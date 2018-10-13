/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::baseAccelerationSynergy()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  // constraint
  VectorXd ddthcRef = pInv(cal_Jc)*cal_dVcBBarRef;

  // mobility
  MatrixXd cal_JmBar = cal_Jm*N(cal_Jc);

  VectorXd cal_dVmTildeRef = cal_dVmBBarRef - cal_Jm*ddthcRef;
  VectorXd ddthmRef = pInv(cal_JmBar)*cal_dVmTildeRef;

  // nonlinear
  VectorXd hc = cal_dPc.transpose()*model->cal_VB + cal_dJc*model->dth;
  VectorXd hm = -dBm.transpose()*model->cal_V + cal_dPm.transpose()*model->cal_VB + cal_dJm*model->dth;

  VectorXd h = pInv(cal_Jc)*hc + pInv(cal_JmBar)*(hm - cal_Jm*pInv(cal_Jc)*hc);

  ddthRef = ddthcRef + ddthmRef - h;

  ddqBRef <<
    fb.cal_dVBfb,
    ddthRef;

  return ddqBRef;
}
