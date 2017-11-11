#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeRlsDynamicsDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.solver.input=="velocity")
    makeVelocityDat(config, info);
  else if(config.solver.input=="acceleration")
    makeAccelerationDat(config, info);
  else if(config.solver.input=="torque")
    makeDynamicsDat(config, info);
}
