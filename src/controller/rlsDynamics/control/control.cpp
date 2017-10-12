#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::control(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  accelerationController(config, info, model);
  momentumController(config, info, model);
  forceController(config, info, model);

  torqueController(config, info, model);
}
