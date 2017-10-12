#include "config.hpp"
#include "info.hpp"

void RLS::Info::initialize(Config &config)
{
  if(config.flag.debug) DEBUG;

  sim.twf = 0.;
  sim.tw0 = 0.;
  sim.phase = 0;

  value.all = 0;
  value.joint = 0;
  dof.all = 0;
  dof.joint = 0;
}
