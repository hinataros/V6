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
  VectorXd ddthcRef = pInv(constraintModel.cal_JcHat)*cal_dVcCBarRef;

  // mobility
  MatrixXd cal_JmCBar = constraintModel.cal_JmHat*N(constraintModel.cal_JcHat);

  VectorXd cal_dVmCTildeRef = cal_dVmCBarRef - constraintModel.cal_JmHat*ddthcRef;
  VectorXd ddthmRef = pInv(cal_JmCBar)*cal_dVmCTildeRef;

  // nonlinear
  VectorXd hcC =
    constraintModel.mbb_dCcM.transpose()*model->cal_VC
    + constraintModel.cal_dJcHat*model->dth;
  VectorXd hmC =
    -constraintModel.dBm.transpose()*model->cal_V
    + constraintModel.mbb_dCmM.transpose()*model->cal_VC
    + constraintModel.cal_dJmHat*model->dth;

  VectorXd h =
    pInv(constraintModel.cal_JcHat)*hcC
    + pInv(cal_JmCBar)*(hmC - constraintModel.cal_JmHat*pInv(constraintModel.cal_JcHat)*hcC);

  VectorXd ddthnRef = N(constraintModel.cal_JcHat)*N(cal_JmCBar)*ddthD();

  ddthRef = ddthcRef + ddthmRef + ddthnRef- h;

  // ddqMRef <<
  //   cal_dVMRef,
  //   ddthRef;

  return ddqMRef;
}
