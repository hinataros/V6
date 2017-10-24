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

  dq <<
    cal_VB,
    model.all.dth;

  IB = model.all.M.block(3,3,3,3);
  HBth = model.all.M.block(0,6,6,info.dof.joint);
  Mth = model.all.M.block(6,6,info.dof.joint,info.dof.joint);

  cal_CB = model.all.c.head(6);
  cal_GB = model.all.g.head(6);

  cth = model.all.c.tail(info.dof.joint);
  gth = model.all.g.tail(info.dof.joint);

  // centroidal motion of eq
  BJC = HBth.block(0,0,3,info.dof.joint) / model.all.m;

  MthC = Mth - model.all.m*BJC.transpose()*BJC;
  cal_GC.head(3) = cal_GB.head(3);
  // cal_CM.tail(3) = dIC*model.limb[0].node[0].w + dHC*model.all.dth;
  cthC = cth - BJC.transpose()*cal_CB.head(3);
}
