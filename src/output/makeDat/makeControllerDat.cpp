#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeControllerDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.name=="rlsVelocity")
    makeRlsVelocityDat(config, info);
  if(config.controller.name=="rlsAcceleration")
    makeRlsAccelerationDat(config, info);
  if(config.controller.name=="rlsDynamics")
    makeRlsDynamicsDat(config, info);
}
