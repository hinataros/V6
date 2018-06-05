/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::baseVelocitySynergy(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // constraint
  VectorXd cal_VcBarRef = -cal_Pc.transpose()*cal_VBRef;

  VectorXd dthcRef = pInv(cal_Jc)*cal_VcBarRef;

  // mobility
  MatrixXd cal_JmBar = cal_Jm*N(cal_Jc);
  VectorXd cal_VmBarRef = Bm.transpose()*cal_VRef - cal_Pm.transpose()*cal_VBRef;
  VectorXd cal_VmTildeRef = cal_VmBarRef - cal_Jm*pInv(cal_Jc)*cal_VcBarRef;

  VectorXd dthmRef = pInv(cal_JmBar)*cal_VmTildeRef;

  dthRef = dthcRef + dthmRef;

  dqBRef <<
    cal_VBRef,
    dthRef;

  VectorXd dqcRef = VectorXd::Zero(info.dof.all);
  dqcRef <<
    bb_ScB*cal_VBRef,
    dthRef;

  return dqcRef;
}
