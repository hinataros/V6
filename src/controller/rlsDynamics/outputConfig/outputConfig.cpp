#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputConfig(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(config.solver.input=="velocity")
    velocityOutputConfig(config, model);

  else if(config.solver.input=="acceleration")
    accelerationOutputConfig(config, model);

  else if(config.solver.input=="torque")
    torqueOutputConfig(config, model);
}
