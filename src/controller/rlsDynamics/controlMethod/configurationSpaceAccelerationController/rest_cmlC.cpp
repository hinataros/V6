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
  VectorXd hcth = cal_dPcM.transpose()*model->cal_VM + cal_dJcM*model->dth;
  VectorXd ddthcRef = pInv(cal_JcM)*(cal_dVcMBarRef - hcth);

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);
  VectorXd cal_dVmTildeRef = cal_dVmMBarRef - cal_JmM*ddthcRef;

  VectorXd hmth = -dBm.transpose()*model->cal_V + cal_dPmM.transpose()*model->cal_VM + cal_dJmM*model->dth;

  VectorXd ddthmRef = N(cal_JcM)*pInv(cal_JmMBar)*(cal_dVmTildeRef - hmth);

  // angular momentum
  MatrixXd HCBar = model->HC*N(cal_JcM)*N(cal_JmMBar);
  // VectorXd dlCDRef = -KDlC*model.hoap2.all.lC;
  VectorXd dlCthRef = dlCRef - model->IC*fb.dwBfb;
  VectorXd dlCTildeRef = dlCthRef - model->HC*(ddthcRef + ddthmRef);

  VectorXd ddthlCRef = N(cal_JcM)*N(cal_JmMBar)*pInv(HCBar)*(dlCTildeRef - model->cmm);

  // redundancy
  VectorXd ddthnRef = N(cal_JcM)*N(cal_JmMBar)*N(HCBar)*ddthD();

  ddthRef = ddthcRef + ddthmRef + ddthlCRef + ddthnRef;

  ddqMRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMRef;
}
