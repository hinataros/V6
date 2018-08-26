/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rest_cmlC(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // constraint
  VectorXd cal_dVcTildeRef = -cal_PcM.transpose()*cal_dVMRef;
  VectorXd hcth = cal_dPcM.transpose()*cal_VM + cal_dJcM*dth;

  VectorXd ddthcRef = pInv(cal_JcM)*(cal_dVcTildeRef - hcth);

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);
  VectorXd cal_dVmthRef = Bm.transpose()*cal_dVRef - cal_PmM.transpose()*cal_dVMRef;
  VectorXd cal_dVmTildeRef = cal_dVmthRef - cal_JmM*ddthcRef;

  VectorXd hmth = -dBm.transpose()*cal_V + cal_dPmM.transpose()*cal_VM + cal_dJmM*dth;

  VectorXd ddthmRef = N(cal_JcM)*pInv(cal_JmMBar)*(cal_dVmTildeRef - hmth);

  // angular momentum
  MatrixXd HCBar = HC*N(cal_JcM)*N(cal_JmMBar);
  // VectorXd dlCDRef = -KDlC*model.hoap2.all.lC;
  VectorXd dlCthRef = dlCRef - IC*dwBRef;
  VectorXd dlCTildeRef = dlCthRef - HC*(ddthcRef + ddthmRef);

  VectorXd ddthlCRef = N(cal_JcM)*N(cal_JmMBar)*pInv(HCBar)*(dlCTildeRef - cmm);

  // redundancy
  VectorXd ddthnRef = N(cal_JcM)*N(cal_JmMBar)*N(HCBar)*ddthD(info);

  ddthRef = ddthcRef + ddthmRef + ddthlCRef + ddthnRef;

  ddqMRef <<
    cal_dVMRef,
    ddthRef;

  return ddqMRef;
}
