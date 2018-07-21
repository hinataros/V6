/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameOthers(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // forward kinematics for kinematics simulation
  for(int i=0; i<6; i++)
    if(!info.contact.c.axis[i]==0)
      bb_ScB(i,i) = 1;
}
