/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::centroidalAccelerationSynergy(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // constraint
  VectorXd cal_dVcCBarRef = -cal_PcM.transpose()*cal_dVCRef;

  VectorXd ddthcRef = pInv(cal_JcHat)*cal_dVcCBarRef;

  // mobility
  MatrixXd cal_JmCBar = cal_JmHat*N(cal_JcHat);
  VectorXd cal_dVmCBarRef = Bm.transpose()*cal_dVRef - cal_PmM.transpose()*cal_dVCRef;
  VectorXd cal_dVmCTildeRef = cal_dVmCBarRef - cal_JmHat*ddthcRef;

  VectorXd ddthmRef = pInv(cal_JmCBar)*cal_dVmCTildeRef;

  // nonlinear
  VectorXd hcC = cal_dPcM.transpose()*cal_VC + cal_dJcHat*dth;
  VectorXd hmC = -dBm.transpose()*cal_V + cal_dPmM.transpose()*cal_VC + cal_dJmHat*dth;

  VectorXd h = pInv(cal_JcHat)*hcC + pInv(cal_JmCBar)*(hmC - cal_JmHat*pInv(cal_JcHat)*hcC);

  VectorXd ddthnRef = N(cal_JcHat)*N(cal_JmCBar)*ddthD(info);

  ddthRef = ddthcRef + ddthmRef + ddthnRef- h;

  // ddqMRef <<
  //   cal_dVMRef,
  //   ddthRef;

  return ddqMRef;
}
