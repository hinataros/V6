/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameBase(TreeModel &model)
{
  if(debug) DEBUG;

  rB2C = rC - rB;
  drB2C = vC - vB;

  if(model.info.contact.c.all)
    Jc <<
      cal_Pc.transpose(), cal_Jc;
  if(model.info.contact.m.all)
    Jm <<
      cal_Pm.transpose(), cal_Jm;

  // diff
  if(model.info.contact.c.all)
    dJc <<
      cal_dPc.transpose(), cal_dJc;
  if(model.info.contact.m.all)
    dJm <<
      cal_dPm.transpose(), cal_dJm;

  // ******************************
  // inertia
  IB = model.all.M.block(3,3,3,3);
  MB = model.all.M.block(0,0,6,6);
  HBth = model.all.M.block(0,6,6,model.info.dof.joint);
  cal_AB = model.all.M.block(0,0,6,model.info.dof.all);

  Mth = model.all.M.block(6,6,model.info.dof.joint,model.info.dof.joint);

  // nonlinear
  cal_dAB = model.all.dM.block(0,0,6,model.info.dof.all);
  cal_CB = model.all.c.head(6);
  cal_GB = model.all.g.head(6);
  cth = model.all.c.tail(model.info.dof.joint);

  // gravity
  gth = model.all.g.tail(model.info.dof.joint);
}
