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
    model.limb[0].node[0].v,
    model.limb[0].node[0].w,
    model.all.dth;

  IB = model.all.M.block(3,3,3,3);
  HBth = model.all.M.block(0,6,6,info.dof.joint);
  Mth = model.all.M.block(6,6,info.dof.joint,info.dof.joint);

  cal_AB << model.all.M.block(0,0,6,6), HBth;
  cal_dAB = model.all.dM.block(0,0,6,info.dof.all);

  cB = model.all.c.head(6);
  gB = model.all.g.head(6);

  cth = model.all.c.tail(info.dof.joint);
  gth = model.all.g.tail(info.dof.joint);
}
