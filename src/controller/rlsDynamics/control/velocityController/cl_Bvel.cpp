#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::cl_Bvel(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // constraint
  VectorXd cal_VcBarRef = -cal_Pc.transpose()*cal_VBRef;

  VectorXd dthcRef = pInv(cal_Jc)*cal_VcBarRef;

  // mobility
  VectorXd cal_VmBarRef = Bm.transpose()*cal_VRef - cal_Pm.transpose()*cal_VBRef;
  VectorXd cal_VmTildeRef = cal_VmBarRef - cal_Jm*pInv(cal_Jc)*cal_VcBarRef;
  VectorXd cal_JmBar = cal_Jm*N(cal_Jc);

  VectorXd dthmRef = pInv(cal_JmBar)*cal_VmTildeRef;

  dthRef = dthcRef + dthmRef;

  dqRef <<
    -cal_Pc.block(0,0,6,6).transpose().inverse()*(cal_Jc*dthRef).head(6),
    dthRef;

  return dqRef;
}
