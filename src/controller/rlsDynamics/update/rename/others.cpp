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

  rB2C = rC - rB;
  drB2C = vC - vB;

  JB2C = model.hoap2.all.JB2C;
  dJB2C = model.hoap2.all.dJB2C;

  // forward kinematics for kinematics simulation
  for(int i=0; i<6; i++)
    if(!model.hoap2.info.contact.c.axis[i]==0)
      bb_ScB(i,i) = 1;
}
