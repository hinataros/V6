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
  // cal_VmBarRef = Bm.transpose()*cal_VRef - cal_Pm.transpose()*cal_VBRef;
  // cal_VmTildeRef = cal_VmBarRef - cal_Jm*pInv(cal_Jc)*cal_VcBarRef;
  // cal_JmBar = cal_Jm*N(cal_Jc);

  // dthmRef = pInv(cal_JmBar)*cal_VmTildeRef;

  dthRef = dthcRef;

  dqMRef <<
    cal_VMRef,
    dthRef;

  return dqMRef;
}
