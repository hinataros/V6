/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedVelocitySynergy(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // constraint
  VectorXd cal_VcBarRef = -cal_PcM.transpose()*cal_VMRef;

  VectorXd dthcRef = pInv(cal_JcM)*cal_VcBarRef;

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);
  VectorXd cal_VmMBarRef = Bm.transpose()*cal_VRef - cal_PmM.transpose()*cal_VMRef;
  VectorXd cal_VmMTildeRef = cal_VmMBarRef - cal_JmM*dthcRef;

  VectorXd dthmRef = pInv(cal_JmMBar)*cal_VmMTildeRef;

  // VectorXd dthnRef = N(cal_JcM)*N(cal_JmMBar)*dthaRef;

  dthRef = dthcRef + dthmRef;

  dqMRef <<
    cal_VMRef,
    dthRef;

  VectorXd dqcRef = VectorXd::Zero(info.dof.all);
  dqcRef <<
    bb_ScB.block(0,0,3,3)*(vCRef + cross(rB2C)*wBRef - JB2C*dthRef),
    bb_ScB.block(3,3,3,3)*wBRef,
    dthRef;

  return dqcRef;
}
