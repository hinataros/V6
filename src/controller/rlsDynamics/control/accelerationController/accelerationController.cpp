#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::accelerationController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // cl_Bcoord(config, model);

  // noname(config, info, model);

  ddthRef = ddthD(config, model);
}
