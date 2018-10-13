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
  VectorXd ddthcRef = pInv(cal_JcM)*cal_dVcMBarRef;

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);

  VectorXd cal_dVmMTildeRef = cal_dVmMBarRef - cal_JmM*ddthcRef;
  VectorXd ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef;

  // nonlinear
  VectorXd hcM = cal_dPcM.transpose()*model->cal_VM + cal_dJcM*model->dth;
  VectorXd hmM = -dBm.transpose()*model->cal_V + cal_dPmM.transpose()*model->cal_VM + cal_dJmM*model->dth;

  VectorXd h = pInv(cal_JcM)*hcM + pInv(cal_JmMBar)*(hmM - cal_JmM*pInv(cal_JcM)*hcM);

  ddthRef = ddthcRef + ddthmRef - h;

  ddqMRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMRef;
}
