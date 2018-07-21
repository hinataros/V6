/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameBase(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_XB <<
    model.hoap2.limb[0].node[0].r,
    R2xi(model.hoap2.limb[0].node[0].R);

  cal_VB <<
    model.hoap2.limb[0].node[0].v,
    model.hoap2.limb[0].node[0].w;

  dq <<
    cal_VB,
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
}
