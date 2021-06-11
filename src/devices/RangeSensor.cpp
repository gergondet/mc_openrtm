#include <mc_openrtm/devices/RangeSensor.h>

namespace mc_openrtm
{

RangeSensor::RangeSensor(const std::string & name, const std::string & parent, const sva::PTransformd & X_p_s)
: mc_rbdyn::Device(name, parent, X_p_s)
{
}

mc_rbdyn::DevicePtr RangeSensor::clone() const
{
  return mc_rbdyn::DevicePtr(new RangeSensor(name_, parent_, X_p_s_));
}

void RangeSensor::update(const RTC::RangeData & data)
{
  config_.minAngle = data.config.minAngle;
  config_.maxAngle = data.config.maxAngle;
  config_.angularRes = data.config.angularRes;
  config_.minRange = data.config.minRange;
  config_.maxRange = data.config.maxRange;
  config_.rangeRes = data.config.rangeRes;
  config_.frequency = data.config.frequency;
  data_.resize(data.ranges.length());
  for(unsigned int i = 0; i < data.ranges.length(); ++i)
  {
    data_[i] = data.ranges[i];
  }
}

} // namespace mc_openrtm
