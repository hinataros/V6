#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsAcceleration.hpp"

void RLS::RlsAcceleration::accelerationController(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  cl_Bcoord(config, model);
}
