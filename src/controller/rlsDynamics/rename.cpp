#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::rename(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_XB <<
    model.limb[0].node[0].r,
    R2xi(model.limb[0].node[0].R);

  cal_VB <<
    model.limb[0].node[0].v,
    model.limb[0].node[0].w;

  cal_VM <<
    model.all.vC,
    model.limb[0].node[0].w;

  rB2C = model.all.rC - model.limb[0].node[0].r;
  drB2C = model.all.vC - model.limb[0].node[0].v;

  // ******************************
  // inertia
  IB = model.all.M.block(3,3,3,3);
  MB = model.all.M.block(0,0,6,6);
  HBth = model.all.M.block(0,6,6,info.dof.joint);
  Mth = model.all.M.block(6,6,info.dof.joint,info.dof.joint);

  // nonlinear
  cal_CB = model.all.c.head(6);
  cal_GB = model.all.g.head(6);
  cth = model.all.c.tail(info.dof.joint);

  // gravity
  gth = model.all.g.tail(info.dof.joint);

  // centroidal
  // ******************************
  Pcf = cal_Pc.block(0,0,3,c);
  Pmf = cal_Pm.block(0,0,3,m);
  PcMm = cal_Pc.block(3,0,3,c);
  cal_JcM = cal_Jc - Pcf.transpose()*model.all.JB2C;
  cal_JmM = cal_Jm - Pmf.transpose()*model.all.JB2C;

  // diff
  dPcf = cal_dPc.block(0,0,3,c);
  dPmf = cal_dPm.block(0,0,3,m);
  dPcMm = cal_dPc.block(3,0,3,c);
  cal_dJcM = cal_dJc - Pcf.transpose()*model.all.dJB2C;
  cal_dJmM = cal_dJm - Pmf.transpose()*model.all.dJB2C;

  // ******************************
  // inertia
  IC = model.all.MM.block(3,3,3,3);
  HC = model.all.MM.block(3,6,3,info.dof.joint);
  MthC = model.all.MM.block(6,6,info.dof.joint,info.dof.joint);

  // diff inertia
  dIC = model.all.dMM.block(3,3,3,3);
  dHC = model.all.dMM.block(3,6,3,info.dof.joint);

  // nonlinear
  cthC = cth - model.all.JB2C.transpose()*cal_CB.head(3);

  // gravity
  gf = cal_GB.head(3);
  cal_GC.head(3) = gf;

  // ******************************
}
