/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reconfigure()
{
  if(debug) DEBUG;

  info.constraint.c.all = Bc_kDiag.diagonal().sum();
  info.constraint.m.all = Bm_kDiag.diagonal().sum();

  for(int i=0; i<info.model.controlNodeNum; i++){
    info.constraint.c.controlNode[i] = Bc_kDiag.block(6*i,6*i,6,6).diagonal().sum();
    info.constraint.m.controlNode[i] = Bm_kDiag.block(6*i,6*i,6,6).diagonal().sum();

    // smiyahara: closed loop formulation におけるforward kinematicsのため
    for(int j=0; j<6; j++)
      info.constraint.c.axis[j] += Bc_kDiag(6*i+j,6*i+j);
  }

  Bc_k = MatrixXd::Zero(6*info.model.controlNodeNum, info.constraint.c.all);
  Bm_k = MatrixXd::Zero(6*info.model.controlNodeNum, info.constraint.m.all);
  for(int i=0, ci=0, mi=0; i<6*info.model.controlNodeNum; i++){
    if(Bc_kDiag(i, i)){
      Bc_k(i,ci) = 1.;
      ci++;
    }
    if(Bm_kDiag(i, i)){
      Bm_k(i,mi) = 1.;
      mi++;
    }
  }

  Bp = MatrixXd::Zero(2*info.model.controlNodeNum, BpDiag.diagonal().sum());
  for(int i=0, pi=0; i<2*info.model.controlNodeNum; i++)
    if(BpDiag(i, i)){
      Bp(i,pi) = 1.;
      pi++;
    }

  // ******************************
  Bc = MatrixXd::Zero(6*info.model.controlNodeNum, info.constraint.c.all);
  Bm = MatrixXd::Zero(6*info.model.controlNodeNum, info.constraint.m.all);

  // diff
  dBc = MatrixXd::Zero(6*info.model.controlNodeNum, info.constraint.c.all);
  dBm = MatrixXd::Zero(6*info.model.controlNodeNum, info.constraint.m.all);

  // ******************************
  cal_Pc = MatrixXd::Zero(6, info.constraint.c.all);
  cal_Pm = MatrixXd::Zero(6, info.constraint.m.all);

  cal_Jc = MatrixXd::Zero(info.constraint.c.all, info.model.dof.joint);
  cal_Jm = MatrixXd::Zero(info.constraint.m.all, info.model.dof.joint);

  Jc = MatrixXd::Zero(info.constraint.c.all, info.model.dof.all);
  Jm = MatrixXd::Zero(info.constraint.m.all, info.model.dof.all);

  // diff
  dJc = MatrixXd::Zero(info.constraint.c.all, info.model.dof.all);
  dJm = MatrixXd::Zero(info.constraint.m.all, info.model.dof.all);

  // diff
  cal_dPc = MatrixXd::Zero(6, info.constraint.c.all);
  cal_dPm = MatrixXd::Zero(6, info.constraint.m.all);

  cal_dJc = MatrixXd::Zero(info.constraint.c.all, info.model.dof.joint);
  cal_dJm = MatrixXd::Zero(info.constraint.m.all, info.model.dof.joint);

  // ******************************
  Pcf = MatrixXd::Zero(3, info.constraint.c.all);
  PcMm = MatrixXd::Zero(3, info.constraint.c.all);
  cal_PcM = MatrixXd::Zero(6, info.constraint.c.all);
  cal_PmM = MatrixXd::Zero(6, info.constraint.m.all);
  cal_JcM = MatrixXd::Zero(info.constraint.c.all, info.model.dof.joint);
  cal_JmM = MatrixXd::Zero(info.constraint.m.all, info.model.dof.joint);

  // diff
  dPcf = MatrixXd::Zero(3, info.constraint.c.all);
  dPcMm = MatrixXd::Zero(3, info.constraint.c.all);
  cal_dPcM = MatrixXd::Zero(6, info.constraint.c.all);
  cal_dPmM = MatrixXd::Zero(6, info.constraint.m.all);
  cal_dJcM = MatrixXd::Zero(info.constraint.c.all, info.model.dof.joint);
  cal_dJmM = MatrixXd::Zero(info.constraint.m.all, info.model.dof.joint);

  // generalized
  JcM = MatrixXd::Zero(info.constraint.c.all, info.model.dof.all);
  JmM = MatrixXd::Zero(info.constraint.m.all, info.model.dof.all);

  // diff
  dJcM = MatrixXd::Zero(info.constraint.c.all, info.model.dof.all);
  dJmM = MatrixXd::Zero(info.constraint.m.all, info.model.dof.all);

  // ******************************
  cal_JcHat = MatrixXd::Zero(info.constraint.c.all, info.model.dof.joint);
  cal_JmHat = MatrixXd::Zero(info.constraint.m.all, info.model.dof.joint);

  // diff
  cal_dJcHat = MatrixXd::Zero(info.constraint.c.all, info.model.dof.joint);
  cal_dJmHat = MatrixXd::Zero(info.constraint.m.all, info.model.dof.joint);

  // ******************************

  // operational space reference
  cal_VcBarRef = VectorXd::Zero(info.constraint.c.all);
  cal_VmBarRef = VectorXd::Zero(info.constraint.m.all);

  cal_VcBBarRef = VectorXd::Zero(info.constraint.c.all);
  cal_VmBBarRef = VectorXd::Zero(info.constraint.m.all);
  cal_VcMBarRef = VectorXd::Zero(info.constraint.c.all);
  cal_VmMBarRef = VectorXd::Zero(info.constraint.m.all);

  cal_dVcBarRef = VectorXd::Zero(info.constraint.c.all);
  cal_dVmBarRef = VectorXd::Zero(info.constraint.m.all);

  cal_dVcBBarRef = VectorXd::Zero(info.constraint.c.all);
  cal_dVmBBarRef = VectorXd::Zero(info.constraint.m.all);
  cal_dVcMBarRef = VectorXd::Zero(info.constraint.c.all);
  cal_dVmMBarRef = VectorXd::Zero(info.constraint.m.all);
  cal_dVcCBarRef = VectorXd::Zero(info.constraint.c.all);
  cal_dVmCBarRef = VectorXd::Zero(info.constraint.m.all);

  // force
  cal_FcaBarRef = VectorXd::Zero(info.constraint.c.all);
  cal_FcBarRef = VectorXd::Zero(info.constraint.c.all);

  // objective
  // ******************************
  // Pc = MatrixXd::Zero(2*info.constraint.num,6*info.constraint.num);
  Pc = MatrixXd::Zero(2*BpDiag.diagonal().sum()/2,6*(BpDiag.diagonal().sum()/2));
}