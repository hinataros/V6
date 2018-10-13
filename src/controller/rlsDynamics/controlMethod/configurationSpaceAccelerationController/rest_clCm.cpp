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
  VectorXd hcth = cal_dPcM.transpose()*model->cal_VM + cal_dJcM*model->dth;
  VectorXd ddthcRef = pInv(cal_JcM)*(cal_dVcMBarRef - hcth);

  // angular momentum
  MatrixXd HCBar = model->HC*N(cal_JcM);
  // VectorXd dlCDRef = -KDlC*model.hoap2.all.lC;
  VectorXd dlCthRef = dlCRef - model->IC*fb.dwBfb;
  VectorXd dlCTildeRef = dlCthRef - model->HC*ddthcRef;

  VectorXd ddthlCRef = N(cal_JcM)*pInv(HCBar)*(dlCTildeRef - model->cmm);

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM)*N(HCBar);
  VectorXd cal_dVmTildeRef = cal_dVmMBarRef - cal_JmM*ddthlCRef;

  VectorXd hmth = -dBm.transpose()*model->cal_V + cal_dPmM.transpose()*model->cal_VM + cal_dJmM*model->dth;

  VectorXd ddthmRef = N(cal_JcM)*N(HCBar)*pInv(cal_JmMBar)*(cal_dVmTildeRef - hmth);

  // redundancy
  VectorXd ddthnRef = N(cal_JcM)*N(HCBar)*N(cal_JmMBar)*ddthD();

  ddthRef = ddthcRef + ddthlCRef + ddthmRef + ddthnRef;

  // // constraint
  // VectorXd cal_dVcthRef = -cal_PcM.transpose()*cal_dVMRef - cal_dPcM.transpose()*cal_VM;
  // VectorXd cal_Vcth = -cal_PcM.transpose()*cal_VM;

  // VectorXd ddthcRef = pInv(cal_JcM)*(cal_dVcthRef) + dpInv(cal_JcM, cal_dJcM)*cal_Vcth;

  // VectorXd ddthnRef = N(cal_JcM)*ddthD(config, model);

  // ddthRef = ddthcRef + ddthnRef;

  ddqMRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMRef;
}
