/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameOthers(Model &model)
{
  if(debug) DEBUG;

  M = model.hoap2.all.m;

  // forward kinematics for kinematics simulation
  for(int i=0; i<6; i++)
    if(!model.hoap2.info.contact.c.axis[i]==0)
      bb_ScB(i,i) = 1;
}
