/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"

void RLS::Info::initialize(Config &config)
{
  if(config.flag.debug) DEBUG;

  sim.state = -1; //smiyahara: 初期化をconfigurationManagerでやるため

  sim.trev = 0.;
  sim.trecf = 0.;

  sim.twf = 0.;
  sim.tw0 = 0.;
  sim.phase = 0;

  value.joint = 0;
  value.node = 0;
  value.all = 0;
  dof.joint = 0;
  dof.all = 0;

  // contact
  contact.num = 0;
  contact.c.all = contact.m.all = 0;

  for(int i=0; i<6; i++)
    contact.c.axis[i] = contact.m.axis[i] = 0;
}
