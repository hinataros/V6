/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::centroidalAccelerationSynergy()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  // constraint
  VectorXd ddthcRef = pInv(cal_JcHat)*cal_dVcCBarRef;

  // mobility
  MatrixXd cal_JmCBar = cal_JmHat*N(cal_JcHat);

  VectorXd cal_dVmCTildeRef = cal_dVmCBarRef - cal_JmHat*ddthcRef;
  VectorXd ddthmRef = pInv(cal_JmCBar)*cal_dVmCTildeRef;

  // nonlinear
  VectorXd hcC = cal_dPcM.transpose()*model->cal_VC + cal_dJcHat*model->dth;
  VectorXd hmC = -dBm.transpose()*model->cal_V + cal_dPmM.transpose()*model->cal_VC + cal_dJmHat*model->dth;

  VectorXd h = pInv(cal_JcHat)*hcC + pInv(cal_JmCBar)*(hmC - cal_JmHat*pInv(cal_JcHat)*hcC);

  VectorXd ddthnRef = N(cal_JcHat)*N(cal_JmCBar)*ddthD();

  ddthRef = ddthcRef + ddthmRef + ddthnRef- h;

  // ddqMRef <<
  //   cal_dVMRef,
  //   ddthRef;

  return ddqMRef;
}
