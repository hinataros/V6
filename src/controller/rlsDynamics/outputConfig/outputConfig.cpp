/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputConfig(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.input=="velocity")
    velocityOutputConfig(config, model);

  else if(config.controller.input=="acceleration")
    accelerationOutputConfig(config, model);

  else if(config.controller.input=="torque")
    torqueOutputConfig(config, model);
}
