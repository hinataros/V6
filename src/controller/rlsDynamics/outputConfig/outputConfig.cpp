/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputConfig(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.input=="velocity")
    velocityOutputConfig(config, info, model);

  else if(config.controller.input=="acceleration")
    accelerationOutputConfig(config, info, model);

  else if(config.controller.input=="torque")
    torqueOutputConfig(config, info, model);
}
