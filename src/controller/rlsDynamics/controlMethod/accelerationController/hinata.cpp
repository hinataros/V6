/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::hinata(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // constraint
  VectorXd cal_VcMTilde = - cal_PcM.transpose()*cal_VM;
  VectorXd cal_dVcMTildeRef = - cal_PcM.transpose()*cal_dVMRef - cal_dPcM.transpose()*cal_VM;

  VectorXd ddthcRef = pInv(cal_JcM)*cal_dVcMTildeRef + dpInv(cal_JcM, cal_dJcM)*cal_VcMTilde;

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);
  MatrixXd cal_dJmMBar = cal_dJmM*N(cal_JcM) + cal_JmM*dN(cal_JcM, cal_dJcM);
  VectorXd cal_VmMTilde = Bm.transpose()*cal_V - cal_PmM.transpose()*cal_VM - cal_JmM*pInv(cal_JcM)*cal_VcMTilde;
  VectorXd cal_dVmMTildeRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - cal_PmM.transpose()*cal_dVMRef - cal_dPmM.transpose()*cal_VM - cal_JmM*(pInv(cal_JcM)*cal_dVcMTildeRef + dpInv(cal_JcM, cal_dJcM)*cal_VcMTilde) - cal_dJmM*pInv(cal_JcM)*cal_VcMTilde;

  VectorXd ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef + dpInv(cal_JmMBar, cal_dJmMBar)*cal_VmMTilde;

  // relative momentum control
  MatrixXd NN = N(cal_JcM)*N(cal_JmMBar);
  MatrixXd Jw = IC.inverse() * HC;
  MatrixXd dJw = IC*dHC - IC.inverse()*dIC*IC.inverse()*HC; // d(IC^-1)/dt = - IC^-1 * dIC * IC^-1
  MatrixXd JwBar = Jw * NN;
  MatrixXd dJwBar = dJw*NN + Jw*(dN(cal_JcM, cal_dJcM)*N(cal_JmMBar) + N(cal_JcM)*dN(cal_JmMBar, cal_dJmMBar));
  VectorXd wTilde = - Jw*pInv(cal_JcM)*cal_VcMTilde - Jw*pInv(cal_JmMBar)*cal_VmMTilde;
  VectorXd dwTildeRef = - Jw*(pInv(cal_JcM)*cal_dVcMTildeRef + dpInv(cal_JcM, cal_dJcM)*cal_VcMTilde + pInv(cal_JmMBar)*cal_dVmMTildeRef + dpInv(cal_JmMBar, cal_dJmMBar)*cal_VmMTilde) - dJw*(pInv(cal_JcM)*cal_VcMTilde + pInv(cal_JmMBar)*cal_VmMTilde);


  VectorXd ddthwRef = pInv(JwBar)*( dwTildeRef  - KDlC*Jw*model.hoap2.all.dth) + dpInv(JwBar, dJwBar)*(wTilde);

  ddthRef = ddthcRef + ddthmRef + ddthwRef + NN*N(JwBar)*ddthD(config,model);

  // o(Jw*model.hoap2.all.dth);
  // o(Jw*ddthRef + dJw*model.hoap2.all.dth);
  // gc;

  ddqMRef <<
    cal_dVMRef,
    ddthRef;

  return ddqMRef;
}
