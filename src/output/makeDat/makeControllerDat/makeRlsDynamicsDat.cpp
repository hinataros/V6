#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeRlsDynamicsDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.input=="velocity")
    makeVelocityDat(config, info);
  else if(config.controller.input=="acceleration")
    makeAccelerationDat(config, info);
  else if(config.controller.input=="torque")
    makeDynamicsDat(config, info);
}
