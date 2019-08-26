/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rest_cmlC()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  // constraint
  VectorXd hcth =
    constraintModel.cal_dPcM.transpose()*model->cal_VM
    + constraintModel.cal_dJcM*model->dth;
  VectorXd ddthcRef = pInv(constraintModel.cal_JcM)*(cal_dVcMBarRef - hcth);

  // mobility
  MatrixXd cal_JmMBar = constraintModel.cal_JmM*N(constraintModel.cal_JcM);
  VectorXd cal_dVmTildeRef = cal_dVmMBarRef - constraintModel.cal_JmM*ddthcRef;

  VectorXd hmth =
    -constraintModel.dBm.transpose()*model->cal_V
    + constraintModel.cal_dPmM.transpose()*model->cal_VM
    + constraintModel.cal_dJmM*model->dth;

  VectorXd ddthmRef = N(constraintModel.cal_JcM)*pInv(cal_JmMBar)*(cal_dVmTildeRef - hmth);

  // angular momentum
  MatrixXd HCBar = model->HC*N(constraintModel.cal_JcM)*N(cal_JmMBar);
  // VectorXd dlCDRef = -KDlC*model.hoap2.all.lC;
  VectorXd dlThRef = dlCRef - model->IC*fb.dwBfb;
  VectorXd dlCTildeRef = dlThRef - model->HC*(ddthcRef + ddthmRef);

  VectorXd ddthlCRef = N(constraintModel.cal_JcM)*N(cal_JmMBar)*pInv(HCBar)*(dlCTildeRef - model->cmm);

  // redundancy
  // VectorXd ddthnRef = N(constraintModel.cal_JcM)*N(cal_JmMBar)*N(HCBar)*ddthD();
  VectorXd ddthnRef = N(constraintModel.cal_JcM)*N(cal_JmMBar)*ddthD();

  // ddthRef = ddthcRef + ddthmRef + ddthlCRef + ddthnRef;
  ddthRef = ddthcRef + ddthmRef + ddthnRef;

  ddqMRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMRef;
}
