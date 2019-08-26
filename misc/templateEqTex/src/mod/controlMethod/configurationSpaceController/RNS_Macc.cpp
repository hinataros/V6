/**
   @author Ryotaro Hinata
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::RNS_Macc()
{
  if(debug) DEBUG;

  ///*
  VectorXd cal_VcMTilde = - constraintModel.cal_PcM.transpose()*model->cal_VM;
  VectorXd cal_dVcMTildeRef = - constraintModel.cal_PcM.transpose()*fb.cal_dVMfb - constraintModel.cal_dPcM.transpose()*model->cal_VM;

  VectorXd ddthcRef = pInv(constraintModel.cal_JcM)*cal_dVcMTildeRef + dpInv(constraintModel.cal_JcM, constraintModel.cal_dJcM)*cal_VcMTilde;

  // mobility
  MatrixXd cal_JmMBar = constraintModel.cal_JmM*N(constraintModel.cal_JcM);
  MatrixXd cal_dJmMBar = constraintModel.cal_dJmM*N(constraintModel.cal_JcM) + constraintModel.cal_JmM*dN(constraintModel.cal_JcM, constraintModel.cal_dJcM);
  VectorXd cal_VmMTilde = constraintModel.Bm.transpose()*model->cal_V - constraintModel.cal_PmM.transpose()*model->cal_VM - constraintModel.cal_JmM*pInv(constraintModel.cal_JcM)*cal_VcMTilde;
  VectorXd cal_dVmMTildeRef = constraintModel.Bm.transpose()*fb.cal_dVfb + constraintModel.dBm.transpose()*model->cal_V - constraintModel.cal_PmM.transpose()*fb.cal_dVMfb - constraintModel.cal_dPmM.transpose()*model->cal_VM - constraintModel.cal_JmM*(pInv(constraintModel.cal_JcM)*cal_dVcMTildeRef + dpInv(constraintModel.cal_JcM, constraintModel.cal_dJcM)*cal_VcMTilde) - constraintModel.cal_dJmM*pInv(constraintModel.cal_JcM)*cal_VcMTilde;

  VectorXd ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef + dpInv(cal_JmMBar, cal_dJmMBar)*cal_VmMTilde;

  // relative momentum control
  MatrixXd NN = N(constraintModel.cal_JcM)*N(cal_JmMBar);
  MatrixXd Jw = model->IC.inverse() * model->HC;
  MatrixXd dJw = model->IC*model->dHC - model->IC.inverse()*model->dIC*model->IC.inverse()*model->HC; // d(IC^-1)/dt = - IC^-1 * dIC * IC^-1
  MatrixXd JwBar = Jw * NN;
  MatrixXd dJwBar = dJw*NN + Jw*(dN(constraintModel.cal_JcM, constraintModel.cal_dJcM)*N(cal_JmMBar) + N(constraintModel.cal_JcM)*dN(cal_JmMBar, cal_dJmMBar));
  VectorXd wTilde = - Jw*pInv(constraintModel.cal_JcM)*cal_VcMTilde - Jw*pInv(cal_JmMBar)*cal_VmMTilde;
  VectorXd dwTildeRef = - Jw*(pInv(constraintModel.cal_JcM)*cal_dVcMTildeRef + dpInv(constraintModel.cal_JcM, constraintModel.cal_dJcM)*cal_VcMTilde + pInv(cal_JmMBar)*cal_dVmMTildeRef + dpInv(cal_JmMBar, cal_dJmMBar)*cal_VmMTilde) - dJw*(pInv(constraintModel.cal_JcM)*cal_VcMTilde + pInv(cal_JmMBar)*cal_VmMTilde);

  MatrixXd KdwC = 100*MatrixXd::Identity(3,3);

  VectorXd ddthwRef = pInv(JwBar)*(dwTildeRef - KdwC*Jw*model->dth) + dpInv(JwBar, dJwBar)*(wTilde);

  ddthRef = ddthcRef + ddthmRef + ddthwRef + NN*N(JwBar)*ddthD();
  // ddthRef = ddthcRef + ddthmRef + NN*N(JwBar)*ddthD();

  ddqMRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMRef;

}
