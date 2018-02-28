/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reconfigure(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  for(int i=1; i<info.value.node; i++){
    info.limb[i].c = Bc_kDiag.block(6*(i-1),6*(i-1),6,6).diagonal().sum();
    info.limb[i].m = Bm_kDiag.block(6*(i-1),6*(i-1),6,6).diagonal().sum();

    info.contact.c.all = Bc_kDiag.diagonal().sum();
    info.contact.m.all = Bm_kDiag.diagonal().sum();

    // smiyahara: closed loop formulation におけるforward kinematicsのため
    for(int j=0; j<6; j++)
      info.contact.c.axis[j] += Bc_kDiag(6*(i-1)+j,6*(i-1)+j);
  }

  Bc_k = MatrixXd::Zero(6*info.value.joint, info.contact.c.all);
  Bm_k = MatrixXd::Zero(6*info.value.joint, info.contact.m.all);
  for(int i=0, ci=0, mi=0; i<6*info.value.joint; i++){
    if(Bc_kDiag(i, i)){
      Bc_k(i,ci) = 1.;
      ci++;
    }
    if(Bm_kDiag(i, i)){
      Bm_k(i,mi) = 1.;
      mi++;
    }
  }

  Bp = MatrixXd::Zero(2*info.value.joint, BpDiag.diagonal().sum());
  for(int i=0, pi=0; i<2*info.value.joint; i++)
    if(BpDiag(i, i)){
      Bp(i,pi) = 1.;
      pi++;
    }

  // ******************************
  Bc = MatrixXd::Zero(6*info.value.joint, info.contact.c.all);
  Bm = MatrixXd::Zero(6*info.value.joint, info.contact.m.all);

  // diff
  dBc = MatrixXd::Zero(6*info.value.joint, info.contact.c.all);
  dBm = MatrixXd::Zero(6*info.value.joint, info.contact.m.all);

  // ******************************
  cal_Pc = MatrixXd::Zero(6, info.contact.c.all);
  cal_Pm = MatrixXd::Zero(6, info.contact.m.all);

  cal_Jc = MatrixXd::Zero(info.contact.c.all, info.dof.joint);
  cal_Jm = MatrixXd::Zero(info.contact.m.all, info.dof.joint);

  Jc = MatrixXd::Zero(info.contact.c.all, info.dof.all);
  Jm = MatrixXd::Zero(info.contact.m.all, info.dof.all);

  // diff
  dJc = MatrixXd::Zero(info.contact.c.all, info.dof.all);
  dJm = MatrixXd::Zero(info.contact.m.all, info.dof.all);

  // diff
  cal_dPc = MatrixXd::Zero(6, info.contact.c.all);
  cal_dPm = MatrixXd::Zero(6, info.contact.m.all);

  cal_dJc = MatrixXd::Zero(info.contact.c.all, info.dof.joint);
  cal_dJm = MatrixXd::Zero(info.contact.m.all, info.dof.joint);

  // ******************************
  Pcf = MatrixXd::Zero(3, info.contact.c.all);
  PcMm = MatrixXd::Zero(3, info.contact.c.all);
  cal_PcM = MatrixXd::Zero(6, info.contact.c.all);
  cal_PmM = MatrixXd::Zero(6, info.contact.m.all);
  cal_JcM = MatrixXd::Zero(info.contact.c.all, info.dof.joint);
  cal_JmM = MatrixXd::Zero(info.contact.m.all, info.dof.joint);

  // diff
  dPcf = MatrixXd::Zero(3, info.contact.c.all);
  dPcMm = MatrixXd::Zero(3, info.contact.c.all);
  cal_dPcM = MatrixXd::Zero(6, info.contact.c.all);
  cal_dPmM = MatrixXd::Zero(6, info.contact.m.all);
  cal_dJcM = MatrixXd::Zero(info.contact.c.all, info.dof.joint);
  cal_dJmM = MatrixXd::Zero(info.contact.m.all, info.dof.joint);

  // generalized
  JcM = MatrixXd::Zero(info.contact.c.all, info.dof.all);
  JmM = MatrixXd::Zero(info.contact.m.all, info.dof.all);

  // diff
  dJcM = MatrixXd::Zero(info.contact.c.all, info.dof.all);
  dJmM = MatrixXd::Zero(info.contact.m.all, info.dof.all);

  // ******************************
  cal_JcHat = MatrixXd::Zero(info.contact.c.all, info.dof.joint);
  cal_JmHat = MatrixXd::Zero(info.contact.m.all, info.dof.joint);

  // diff
  cal_dJcHat = MatrixXd::Zero(info.contact.c.all, info.dof.joint);
  cal_dJmHat = MatrixXd::Zero(info.contact.m.all, info.dof.joint);

  // ******************************

  // force
  cal_FcBarRef = VectorXd::Zero(info.contact.c.all);

  // objective
  // ******************************
  // Pc = MatrixXd::Zero(2*info.contact.num,6*info.contact.num);
  Pc = MatrixXd::Zero(2*BpDiag.diagonal().sum()/2,6*(BpDiag.diagonal().sum()/2));
}
