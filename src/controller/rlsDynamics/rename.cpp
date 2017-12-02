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

  dq <<
    cal_VB,
    model.all.dth;

  rB2C = model.all.rC - model.limb[0].node[0].r;
  drB2C = model.all.vC - model.limb[0].node[0].v;

  Jc <<
    cal_Pc.transpose(), cal_Jc;
  dJc <<
    cal_dPc.transpose(), cal_dJc;

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

  // o(cth);
  // o(model.all.dM.block(6,6,info.dof.joint,info.dof.joint)*model.all.dth);

  // o(cth- model.all.dM.block(6,6,info.dof.joint,info.dof.joint)*model.all.dth);

  // // o(cthC);
  // // o(cthC - );
  // // o(dHC.transpose()*cal_VM.tail(3) + model.all.dMM.block(6,6,info.dof.joint,info.dof.joint)*model.all.dth);

  // // o(cthC - (dHC.transpose()*cal_VM.tail(3) + model.all.dMM.block(6,6,info.dof.joint,info.dof.joint)*model.all.dth));
  // gc;

  // o(cal_CB);
  // Vector6d cal_CBtemp = Vector6d::Zero();
  // Vector3d temp = model.all.m*cross(drB2C).transpose()*cal_VM.tail(3) + model.all.m*model.all.dJB2C*model.all.dth;
  // cal_CBtemp.head(3) = temp;
  // cal_CBtemp.tail(3) = (dIC + model.all.m*cross(rB2C)*(cross(drB2C).transpose()))*cal_VM.tail(3) + (dHC + model.all.m*cross(rB2C)*model.all.dJB2C)*model.all.dth;
  // cal_CBtemp.tail(3) = dIC*cal_VM.tail(3) + dHC*model.all.dth + cross(rB2C)*temp;
  // cal_CBtemp.tail(3) = -model.all.m*cross(rB2C).transpose()*cal_VB.head(3) + dIB*cal_VM.tail(3) + dHB*model.all.dth;

  // o(cal_CBtemp);
  // o(cal_CB - cal_CBtemp);
  // gc;
  // Vector6d cal_CMtemp = Vector6d::Zero();
  // cal_CMtemp <<
  //   cal_CB.head(3) + model.all.m*cross(drB2C)*cal_VM.tail(3) - model.all.m*model.all.dJB2C*model.all.dth,
  //   -cross(rB2C)*cal_CB.head(3) + cal_CB.tail(3);

  // Vector6d cal_CMtemptemp = Vector6d::Zero();
  // cal_CMtemptemp <<
  //   Vector3d::Zero(),
  //   dIC*cal_VM.tail(3) + dHC*model.all.dth;


  // o(cal_CMtemp);
  // o(cal_CMtemptemp);
  // o(cal_CMtemp - cal_CMtemptemp);
}
