/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"

void RLS::Info::initialize(Config &config)
{
  if(config.flag.debug) DEBUG;

  sim.trev = 0.;
  sim.state = -1; //smiyahara: 初期化をconfigurationManagerでやるため

  sim.twf = 0.;
  sim.tw0 = 0.;
  sim.phase = 0;

  value.all = 0;
  value.joint = 0;
  dof.all = 0;
  dof.joint = 0;
}
