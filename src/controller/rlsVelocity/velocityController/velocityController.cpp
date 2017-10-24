#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::velocityController(Config &config)
{
  if(config.flag.debug) DEBUG;

  cl_Bcoord(config);
}
