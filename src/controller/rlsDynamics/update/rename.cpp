/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::rename(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_XB <<
    model.hoap2.limb[0].node[0].r,
    R2xi(model.hoap2.limb[0].node[0].R);

  cal_VB <<
    model.hoap2.limb[0].node[0].v,
    model.hoap2.limb[0].node[0].w;

  cal_VM <<
    model.hoap2.all.vC,
    model.hoap2.limb[0].node[0].w;

  dq <<
    cal_VB,
    model.hoap2.all.dth;
  dqM <<
    cal_VM,
    model.hoap2.all.dth;

  rB2C = model.hoap2.all.rC - model.hoap2.limb[0].node[0].r;
  drB2C = model.hoap2.all.vC - model.hoap2.limb[0].node[0].v;

  if(info.contact.c.all)
    Jc <<
      cal_Pc.transpose(), cal_Jc;
  if(info.contact.m.all)
    Jm <<
      cal_Pm.transpose(), cal_Jm;

  // diff
  if(info.contact.c.all)
    dJc <<
      cal_dPc.transpose(), cal_dJc;
  if(info.contact.m.all)
    dJm <<
      cal_dPm.transpose(), cal_dJm;

  // ******************************
  // inertia
  IB = model.hoap2.all.M.block(3,3,3,3);
  MB = model.hoap2.all.M.block(0,0,6,6);
  HBth = model.hoap2.all.M.block(0,6,6,info.dof.joint);
  cal_AB = model.hoap2.all.M.block(0,0,6,info.dof.all);

  Mth = model.hoap2.all.M.block(6,6,info.dof.joint,info.dof.joint);

  // nonlinear
  cal_CB = model.hoap2.all.c.head(6);
  cal_GB = model.hoap2.all.g.head(6);
  cth = model.hoap2.all.c.tail(info.dof.joint);

  // gravity
  gth = model.hoap2.all.g.tail(info.dof.joint);

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
  cal_VC <<
    model.hoap2.all.vC,
    model.hoap2.limb[0].node[0].w + IC.inverse()*HC*model.hoap2.all.dth;

  // inertia
  MthHat = Mth - HBth.transpose()*MB.inverse()*HBth;

  // nonlinear
  cthHat = cth - HBth.transpose()*MB.inverse()*cal_CB;
  // ******************************

  // centroidal
  // ******************************
  Pcf = cal_Pc.block(0,0,3,info.contact.c.all);
  Pmf = cal_Pm.block(0,0,3,info.contact.m.all);
  PcMm = cal_PcM.block(3,0,3,info.contact.c.all);
  cal_JcM = cal_Jc - Pcf.transpose()*model.hoap2.all.JB2C;
  cal_JmM = cal_Jm - Pmf.transpose()*model.hoap2.all.JB2C;

  // diff
  dPcf = cal_dPc.block(0,0,3,info.contact.c.all);
  dPmf = cal_dPm.block(0,0,3,info.contact.m.all);
  dPcMm = cal_dPc.block(3,0,3,info.contact.c.all);
  // dPcf = 0と仮定
  cal_dJcM = cal_dJc - Pcf.transpose()*model.hoap2.all.dJB2C;
  cal_dJmM = cal_dJm - Pmf.transpose()*model.hoap2.all.dJB2C;

  // ******************************
  Jth <<
    model.hoap2.all.JB2C,
    IC.inverse()*HC;

  cal_JcHat = cal_Jc - cal_PcM.transpose()*Jth;
  cal_JmHat = cal_Jm - cal_PmM.transpose()*Jth;

  // diff
  dJth <<
    model.hoap2.all.dJB2C,
    IC.inverse()*(dHC - dIC*(IC.inverse()*HC));

  cal_dJcHat = cal_dJc - cal_dPcM.transpose()*Jth - cal_PcM.transpose()*dJth;
  cal_dJmHat = cal_dJm - cal_dPmM.transpose()*Jth - cal_PmM.transpose()*dJth;

  // ******************************
  // forward kinematics for kinematics simulation
  for(int i=0; i<6; i++)
    if(!info.contact.c.axis[i]==0)
      bb_ScB(i,i) = 1;
  // ******************************

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

  // o(cth);
  // o(model.hoap2.all.dM.block(6,6,info.dof.joint,info.dof.joint)*model.hoap2.all.dth);

  // o(cth- model.hoap2.all.dM.block(6,6,info.dof.joint,info.dof.joint)*model.hoap2.all.dth);

  // // o(dHC.transpose()*cal_VM.tail(3) + model.hoap2.all.dMM.block(6,6,info.dof.joint,info.dof.joint)*model.hoap2.all.dth);

  // // o(cthC - (dHC.transpose()*cal_VM.tail(3) + model.hoap2.all.dMM.block(6,6,info.dof.joint,info.dof.joint)*model.hoap2.all.dth));
  // gc;

  // o(cal_CB);
  // Vector3d cBm = model.hoap2.all.dM.block(3,0,3,info.dof.all)*dq + model.hoap2.all.m*cross(drB2C).transpose()*cal_VM.head(3);
  // o(cBm);
  // o(cal_CB.tail(3) - cBm);
  // gc;

  // Vector6d cal_CBtemp = Vector6d::Zero();
  // Vector3d temp = model.hoap2.all.m*cross(drB2C).transpose()*cal_VM.tail(3) + model.hoap2.all.m*model.hoap2.all.dJB2C*model.hoap2.all.dth;
  // cal_CBtemp.head(3) = temp;
  // cal_CBtemp.tail(3) = (dIC + model.hoap2.all.m*cross(rB2C)*(cross(drB2C).transpose()))*cal_VM.tail(3) + (dHC + model.hoap2.all.m*cross(rB2C)*model.hoap2.all.dJB2C)*model.hoap2.all.dth;
  // cal_CBtemp.tail(3) = dIC*cal_VM.tail(3) + dHC*model.hoap2.all.dth + cross(rB2C)*temp;
  // cal_CBtemp.tail(3) = -model.hoap2.all.m*cross(rB2C).transpose()*cal_VB.head(3) + dIB*cal_VM.tail(3) + dHB*model.hoap2.all.dth;

  // o(cal_CBtemp);
  // o(cal_CB - cal_CBtemp);
  // gc;
  // Vector6d cal_CMtemp = Vector6d::Zero();
  // cal_CMtemp <<
  //   cal_CB.head(3) + model.hoap2.all.m*cross(drB2C)*cal_VM.tail(3) - model.hoap2.all.m*model.hoap2.all.dJB2C*model.hoap2.all.dth,
  //   -cross(rB2C)*cal_CB.head(3) + cal_CB.tail(3);

  // Vector6d cal_CMtemptemp = Vector6d::Zero();
  // cal_CMtemptemp <<
  //   Vector3d::Zero(),
  //   dIC*cal_VM.tail(3) + dHC*model.hoap2.all.dth;


  // o(cal_CMtemp);
  // o(cal_CMtemptemp);
  // o(cal_CMtemp - cal_CMtemptemp);
}
