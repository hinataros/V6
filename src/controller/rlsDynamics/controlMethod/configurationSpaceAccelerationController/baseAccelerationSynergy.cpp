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
  VectorXd ddthcRef = pInv(constraintModel.cal_Jc)*cal_dVcBBarRef;

  // mobility
  MatrixXd cal_JmBar = constraintModel.cal_Jm*N(constraintModel.cal_Jc);

  VectorXd cal_dVmTildeRef = cal_dVmBBarRef - constraintModel.cal_Jm*ddthcRef;
  VectorXd ddthmRef = pInv(cal_JmBar)*cal_dVmTildeRef;

  // nonlinear
  VectorXd hc =
    constraintModel.mbb_dCc.transpose()*model->cal_VB
    + constraintModel.cal_dJc*model->dth;
  VectorXd hm =
    -constraintModel.dBm.transpose()*model->cal_V
    + constraintModel.mbb_dCm.transpose()*model->cal_VB
    + constraintModel.cal_dJm*model->dth;

  VectorXd h =
    pInv(constraintModel.cal_Jc)*hc +
    pInv(cal_JmBar)*(hm - constraintModel.cal_Jm*pInv(constraintModel.cal_Jc)*hc);

  ddthRef = ddthcRef + ddthmRef - h;

  ddqBRef <<
    fb.cal_dVBfb,
    ddthRef;

  return ddqBRef;
}
