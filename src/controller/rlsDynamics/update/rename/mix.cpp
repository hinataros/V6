/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameMix(TreeModel &model)
{
  if(debug) DEBUG;

  // ******************************
  // inertia
  IC = model.all.MM.block(3,3,3,3);
  MC = model.all.MM.block(0,0,6,6);
  HMth = model.all.MM.block(0,6,6,model.info.dof.joint);
  HC = model.all.MM.block(3,6,3,model.info.dof.joint);
  cal_AM = model.all.MM.block(0,0,6,model.info.dof.all);

  MthC = model.all.MM.block(6,6,model.info.dof.joint,model.info.dof.joint);

  // diff inertia
  cal_dAM = model.all.dMM.block(0,0,6,model.info.dof.all);
  dIC = model.all.dMM.block(3,3,3,3);
  dHC = model.all.dMM.block(3,6,3,model.info.dof.joint);

  // nonlinear
  cmm = dIC*wB + dHC*dth;
  cal_CM.tail(3) = cmm;
  cthC = cth - model.all.JB2C.transpose()*cal_CB.head(3);

  // gravity
  gf = cal_GB.head(3);
  cal_GC.head(3) = gf;

  // ******************************
  if(model.info.contact.c.all)
    JcM <<
      cal_PcM.transpose(), cal_JcM;
  if(model.info.contact.m.all)
    JmM <<
      cal_PmM.transpose(), cal_JmM;

  // diff
  if(model.info.contact.c.all)
    dJcM <<
      cal_dPcM.transpose(), cal_dJcM;
  if(model.info.contact.m.all)
    dJmM <<
      cal_dPmM.transpose(), cal_dJmM;
  // ******************************
}
