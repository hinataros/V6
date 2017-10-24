#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::rename(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  IB = model.all.M.block(3,3,3,3);
  HBth = model.all.M.block(0,6,6,info.dof.joint);
  Mth = model.all.M.block(6,6,info.dof.joint,info.dof.joint);

  // centroidal motion of eq
  BJC = HBth.block(0,0,3,info.dof.joint) / model.all.m;
}
