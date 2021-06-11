#pragma once

#include <mc_openrtm/devices/api.h>

#include <mc_rbdyn/Device.h>

#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <vector>

namespace mc_openrtm
{

struct RangeSensor;

struct MC_OPENRTM_DEVICES_DLLAPI RangeSensor : public mc_rbdyn::Device
{
  RangeSensor(const std::string & name, const std::string & parent, const sva::PTransformd & X_p_s);

  struct Configuration
  {
    /** Minimum scannable angle in radians */
    double minAngle;
    /** Maximum scannable angle in radians */
    double maxAngle;
    /** Angular resolution in radians */
    double angularRes;
    /** Minimum scannable range in meters */
    double minRange;
    /** Maximum scannable range in meters */
    double maxRange;
    /** Range resolution in meters */
    double rangeRes;
    /** Scanning frequency */
    double frequency;
  };

  /** Return the latest range sensing data, might be empty */
  inline const std::vector<double> & data() const noexcept
  {
    return data_;
  }

  /** Access the RangeSensor configuration
   *
   * This configuration is invalid before data has been received
   */
  inline const Configuration config() const noexcept
  {
    return config_;
  }

  /** Update the sensor configuration and data from an OpenRTM message */
  void update(const RTC::RangeData & data);

  mc_rbdyn::DevicePtr clone() const override;

private:
  Configuration config_;
  std::vector<double> data_;
};

} // namespace mc_openrtm
