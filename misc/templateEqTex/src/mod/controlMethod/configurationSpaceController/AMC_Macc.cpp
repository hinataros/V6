/**
   @author Ryotaro Hinata
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::AMC_Macc(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // ////// 拘束条件の微分から算出 //////
  
  // // constraint
  // VectorXd cal_dVcMTildeRef = -mbb_CcM.transpose()*cal_dVMRef;

  // VectorXd ddthcRef = pInv(cal_JcM)*cal_dVcMTildeRef;

  // // mobility
  // MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);
  // VectorXd cal_dVmMTildeRef = Bm.transpose()*cal_dVRef - mbb_CmM.transpose()*cal_dVMRef - cal_JmM*pInv(cal_JcM)*cal_dVcMTildeRef;

  // VectorXd ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef;

  // // relative momentum control
  // MatrixXd NN = N(cal_JcM)*N(cal_JmMBar);
  // MatrixXd Jw = IC.inverse() * HC;
  // MatrixXd dJw = IC*dHC - IC.inverse()*dIC*IC.inverse()*HC; // d(IC^-1)/dt = - IC^-1 * dIC * IC^-1
  // MatrixXd JwBar = Jw * NN;
  // VectorXd cal_dVwTildeRef = - Jw*pInv(cal_JcM)*cal_dVcMTildeRef - Jw*pInv(cal_JmMBar)*cal_dVmMTildeRef;

  // VectorXd ddthwRef = NN*pInv(JwBar)*( (dwCRef - dwBRef) + cal_dVwTildeRef );

  // // nonlinear
  // VectorXd hcM = cal_dPcM.transpose()*cal_VM + cal_dJcM*model.hoap2.all.dth;
  // VectorXd hmM = -dBm.transpose()*cal_V + cal_dPmM.transpose()*cal_VM + cal_dJmM*model.hoap2.all.dth;
  // VectorXd hw = dJw*model.hoap2.all.dth;

  // VectorXd h = pInv(cal_JcM)*hcM + pInv(cal_JmMBar)*(hmM - cal_JmM*pInv(cal_JcM)*hcM) + NN*pInv(JwBar)*(hw - Jw*pInv(cal_JcM)*hcM - Jw*pInv(cal_JmMBar)*(hmM - cal_JmM*pInv(cal_JcM)*hcM));

  // MatrixXd cal_JB2C = MatrixXd::Zero(6,info.dof.joint);
  // MatrixXd cal_dJB2C = MatrixXd::Zero(6,info.dof.joint);
  // cal_JB2C.block(0,0,3,info.dof.joint) = model.hoap2.all.JB2C;
  // cal_dJB2C.block(0,0,3,info.dof.joint) = model.hoap2.all.dJB2C;
  
  // ddthRef = ddthcRef + ddthmRef + ddthwRef - h + NN*N(JwBar)*ddthD(config, model);

  // // ddqRef <<
  // //   TC2B*cal_dVMRef + dTC2B*cal_VM - cal_JB2C*ddthRef - cal_dJB2C*model.hoap2.all.dth,
  // //   ddthRef;

  // ddqRef <<
  //   cal_dVMRef,
  //   ddthRef;

  // return ddqRef;

  
  ////// 速度次元解の微分 //////

  // constraint
  VectorXd cal_VcMTilde = - mbb_CcM.transpose()*cal_VM;
  VectorXd cal_dVcMTildeRef = - mbb_CcM.transpose()*cal_dVMRef - cal_dPcM.transpose()*cal_VM;

  VectorXd ddthcRef = pInv(cal_JcM)*cal_dVcMTildeRef + dpInv(cal_JcM, cal_dJcM)*cal_VcMTilde;

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);
  MatrixXd cal_dJmMBar = cal_dJmM*N(cal_JcM) + cal_JmM*dN(cal_JcM, cal_dJcM);
  VectorXd cal_VmMTilde = Bm.transpose()*cal_V - mbb_CmM.transpose()*cal_VM - cal_JmM*pInv(cal_JcM)*cal_VcMTilde;
  VectorXd cal_dVmMTildeRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - mbb_CmM.transpose()*cal_dVMRef - cal_dPmM.transpose()*cal_VM - cal_JmM*(pInv(cal_JcM)*cal_dVcMTildeRef + dpInv(cal_JcM, cal_dJcM)*cal_VcMTilde) - cal_dJmM*pInv(cal_JcM)*cal_VcMTilde;

  VectorXd ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef + dpInv(cal_JmMBar, cal_dJmMBar)*cal_VmMTilde;

  // relative momentum control
  MatrixXd NN = N(cal_JcM)*N(cal_JmMBar);
  MatrixXd Jw = IC.inverse() * HC;
  MatrixXd dJw = IC*dHC - IC.inverse()*dIC*IC.inverse()*HC; // d(IC^-1)/dt = - IC^-1 * dIC * IC^-1
  MatrixXd JwBar = Jw * NN;
  MatrixXd dJwBar = dJw*NN + Jw*(dN(cal_JcM, cal_dJcM)*N(cal_JmMBar) + N(cal_JcM)*dN(cal_JmMBar, cal_dJmMBar));
  VectorXd wTilde = - Jw*pInv(cal_JcM)*cal_VcMTilde - Jw*pInv(cal_JmMBar)*cal_VmMTilde;
  VectorXd dwTildeRef = - Jw*(pInv(cal_JcM)*cal_dVcMTildeRef + dpInv(cal_JcM, cal_dJcM)*cal_VcMTilde + pInv(cal_JmMBar)*cal_dVmMTildeRef + dpInv(cal_JmMBar, cal_dJmMBar)*cal_VmMTilde) - dJw*(pInv(cal_JcM)*cal_VcMTilde + pInv(cal_JmMBar)*cal_VmMTilde);

  VectorXd ddthwRef = pInv(JwBar)*( (dwCRef - dwBRef) + dwTildeRef ) + dpInv(JwBar, dJwBar)*(Jw*model.hoap2.all.dth + wTilde);
 
  ddthRef = ddthcRef + ddthmRef + ddthwRef + NN*N(JwBar)*ddthD(config,model);
  ddqMRef <<
    cal_dVMRef,
    ddthRef;

  return ddqMRef;

}
