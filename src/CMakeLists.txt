#
# Copyright 2016-2019 CNRS-UM LIRMM, CNRS-AIST JRL
#

foreach(STUB ${ALL_IDL_CPP_STUBS})
  set_source_files_properties(${STUB} PROPERTIES GENERATED 1 COMPILE_FLAGS -Wno-error)
endforeach()

set(MCControl_SRC
      MCControlServiceSVC_impl.cpp
      MCControl.cpp
      ${ALL_IDL_CPP_STUBS}
)

set(MCControl_HDR
      MCControlServiceSVC_impl.h
      MCControl.h
)


include_directories(${CMAKE_BINARY_DIR}/idl)

add_library(MCControl SHARED ${MCControl_SRC} ${MCControl_HDR})
add_dependencies(MCControl generate_mc_idl_cpp)
set_target_properties(MCControl PROPERTIES PREFIX "")
pkg_config_use_dependency(MCControl hrpsys-base)
target_link_libraries(MCControl PUBLIC mc_rtc::mc_control)
target_include_directories(MCControl PRIVATE "${PROJECT_BINARY_DIR}/idl")

add_executable(MCControlComp MCControlComp.cpp)
target_link_libraries(MCControlComp PUBLIC MCControl)

install(TARGETS MCControl MCControlComp
  RUNTIME DESTINATION "${HRPSYS_BASE_PREFIX}/bin"
  LIBRARY DESTINATION "${HRPSYS_BASE_PREFIX}/lib"
  ARCHIVE DESTINATION "${HRPSYS_BASE_PREFIX}/lib"
)

set(devices_INC "${PROJECT_SOURCE_DIR}/include/mc_openrtm/devices")
set(devices_BINC "${PROJECT_BINARY_DIR}/include/mc_openrtm/devices")
set(devices_HDR
  ${devices_INC}/RangeSensor.h
)
set(devices_SRC
  devices/RangeSensor.cpp
)
configure_file("${devices_INC}/api.in.h" "${devices_BINC}/api.h" @ONLY)
list(APPEND devices_HDR "${devices_BINC}/api.h")

add_library(mc_openrtm_devices SHARED ${devices_SRC} ${devices_HDR})
add_library(mc_openrtm::devices ALIAS mc_openrtm_devices)
set_target_properties(mc_openrtm_devices PROPERTIES EXPORT_NAME devices)
target_include_directories(mc_openrtm_devices PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries(mc_openrtm_devices PUBLIC mc_rtc::mc_rbdyn)
target_compile_definitions(mc_openrtm_devices PRIVATE -DMC_OPENRTM_DEVICES_EXPORTS)
pkg_config_use_dependency(mc_openrtm_devices hrpsys-base)
install(FILES ${devices_HDR} DESTINATION include/mc_openrtm/devices)
install(TARGETS mc_openrtm_devices
  EXPORT ${TARGETS_EXPORT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
