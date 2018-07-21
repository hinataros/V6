/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameMix(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_VM <<
    model.hoap2.all.vC,
    model.hoap2.limb[0].node[0].w;

  dqM <<
    cal_VM,
    model.hoap2.all.dth;

  // ******************************
  // inertia
  IC = model.hoap2.all.MM.block(3,3,3,3);
  MC = model.hoap2.all.MM.block(0,0,6,6);
  HMth = model.hoap2.all.MM.block(0,6,6,info.dof.joint);
  HC = model.hoap2.all.MM.block(3,6,3,info.dof.joint);
  cal_AM = model.hoap2.all.MM.block(0,0,6,info.dof.all);

  MthC = model.hoap2.all.MM.block(6,6,info.dof.joint,info.dof.joint);

  // diff inertia
  dIC = model.hoap2.all.dMM.block(3,3,3,3);
  dHC = model.hoap2.all.dMM.block(3,6,3,info.dof.joint);

  // nonlinear
  cal_CM.tail(3) = dIC*cal_VM.tail(3) + dHC*model.hoap2.all.dth;
  cthC = cth - model.hoap2.all.JB2C.transpose()*cal_CB.head(3);

  // gravity
  gf = cal_GB.head(3);
  cal_GC.head(3) = gf;

  // ******************************
  if(info.contact.c.all)
    JcM <<
      cal_PcM.transpose(), cal_JcM;
  if(info.contact.m.all)
    JmM <<
      cal_PmM.transpose(), cal_JmM;

  // diff
  if(info.contact.c.all)
    dJcM <<
      cal_dPcM.transpose(), cal_dJcM;
  if(info.contact.m.all)
    dJmM <<
      cal_dPmM.transpose(), cal_dJmM;
  // ******************************
}
