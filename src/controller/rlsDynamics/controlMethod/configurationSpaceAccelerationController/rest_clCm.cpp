/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rest_clCm()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  // constraint
  VectorXd hcth =
    constraintModel.mbb_dCcM.transpose()*model->cal_VM
    + constraintModel.cal_dJcM*model->dth;
  VectorXd ddthcRef = pInv(constraintModel.cal_JcM)*(cal_dVcMBarRef - hcth);

  // angular momentum
  MatrixXd HCBar = model->HC*N(constraintModel.cal_JcM);
  // VectorXd dlCDRef = -KDlC*model.hoap2.all.lC;
  VectorXd dlThRef = dlCRef - model->IC*fb.dwBfb;
  VectorXd dlCTildeRef = dlThRef - model->HC*ddthcRef;

  VectorXd ddthlCRef = N(constraintModel.cal_JcM)*pInv(HCBar)*(dlCTildeRef - model->cmm);

  // mobility
  MatrixXd cal_JmMBar = constraintModel.cal_JmM*N(constraintModel.cal_JcM)*N(HCBar);
  VectorXd cal_dVmTildeRef = cal_dVmMBarRef - constraintModel.cal_JmM*ddthlCRef;

  VectorXd hmth =
    -constraintModel.dBm.transpose()*model->cal_V
    + constraintModel.mbb_dCmM.transpose()*model->cal_VM
    + constraintModel.cal_dJmM*model->dth;

  VectorXd ddthmRef = N(constraintModel.cal_JcM)*N(HCBar)*pInv(cal_JmMBar)*(cal_dVmTildeRef - hmth);

  // redundancy
  VectorXd ddthnRef = N(constraintModel.cal_JcM)*N(HCBar)*N(cal_JmMBar)*ddthD();

  ddthRef = ddthcRef + ddthlCRef + ddthmRef + ddthnRef;

  // // constraint
  // VectorXd cal_dVcthRef = -mbb_CcM.transpose()*cal_dVMRef - mbb_dCcM.transpose()*cal_VM;
  // VectorXd cal_Vcth = -mbb_CcM.transpose()*cal_VM;

  // VectorXd ddthcRef = pInv(cal_JcM)*(cal_dVcthRef) + dpInv(cal_JcM, cal_dJcM)*cal_Vcth;

  // VectorXd ddthnRef = N(cal_JcM)*ddthD(config, model);

  // ddthRef = ddthcRef + ddthnRef;

  ddqMRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMRef;
}
