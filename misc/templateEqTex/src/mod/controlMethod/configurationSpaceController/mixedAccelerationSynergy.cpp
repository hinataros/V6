/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedAccelerationSynergy()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  // constraint
  VectorXd ddthcRef = pInv(constraintModel.cal_JcM)*cal_dVcMBarRef;

  // mobility
  MatrixXd cal_JmMBar = constraintModel.cal_JmM*N(constraintModel.cal_JcM);

  VectorXd cal_dVmMTildeRef = cal_dVmMBarRef - constraintModel.cal_JmM*ddthcRef;
  VectorXd ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef;

  // nonlinear
  VectorXd hcM =
    constraintModel.cal_dPcM.transpose()*model->cal_VM
    + constraintModel.cal_dJcM*model->dth;
  VectorXd hmM =
    -constraintModel.dBm.transpose()*model->cal_V
    + constraintModel.cal_dPmM.transpose()*model->cal_VM
    + constraintModel.cal_dJmM*model->dth;

  VectorXd h =
    pInv(constraintModel.cal_JcM)*hcM
    + pInv(cal_JmMBar)*(hmM - constraintModel.cal_JmM*pInv(constraintModel.cal_JcM)*hcM);

  ddthRef = ddthcRef + ddthmRef - h;

  ddqMRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMRef;
}
