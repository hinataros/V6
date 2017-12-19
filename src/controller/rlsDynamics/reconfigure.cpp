#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reconfigure(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  c = Bc_kDiag.diagonal().sum();
  m = Bm_kDiag.diagonal().sum();

  Bc_k = MatrixXd::Zero(6*info.value.joint, c);
  Bm_k = MatrixXd::Zero(6*info.value.joint, m);
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

  // ******************************
  Bc = MatrixXd::Zero(6*info.value.joint, c);
  Bm = MatrixXd::Zero(6*info.value.joint, m);

  // diff
  dBc = MatrixXd::Zero(6*info.value.joint, c);
  dBm = MatrixXd::Zero(6*info.value.joint, m);

  // ******************************
  cal_Pc = MatrixXd::Zero(6, c);
  cal_Pm = MatrixXd::Zero(6, m);

  cal_Jc = MatrixXd::Zero(c, info.dof.joint);
  cal_Jm = MatrixXd::Zero(m, info.dof.joint);

  Jc = MatrixXd::Zero(c, info.dof.all);
  Jm = MatrixXd::Zero(m, info.dof.all);

  // diff
  dJc = MatrixXd::Zero(c, info.dof.all);
  dJm = MatrixXd::Zero(m, info.dof.all);

  // diff
  cal_dPc = MatrixXd::Zero(6, c);
  cal_dPm = MatrixXd::Zero(6, m);

  cal_dJc = MatrixXd::Zero(c, info.dof.joint);
  cal_dJm = MatrixXd::Zero(m, info.dof.joint);

  // ******************************
  Pcf = MatrixXd::Zero(3, c);
  PcMm = MatrixXd::Zero(3, c);
  cal_PcM = MatrixXd::Zero(6, c);
  cal_PmM = MatrixXd::Zero(6, m);
  cal_JcM = MatrixXd::Zero(c, info.dof.joint);
  cal_JmM = MatrixXd::Zero(m, info.dof.joint);

  // diff
  dPcf = MatrixXd::Zero(3, c);
  dPcMm = MatrixXd::Zero(3, c);
  cal_dPcM = MatrixXd::Zero(6, c);
  cal_dPmM = MatrixXd::Zero(6, m);
  cal_dJcM = MatrixXd::Zero(c, info.dof.joint);
  cal_dJmM = MatrixXd::Zero(m, info.dof.joint);

  // ******************************
  cal_JcHat = MatrixXd::Zero(c, info.dof.joint);
  cal_JmHat = MatrixXd::Zero(m, info.dof.joint);

  // diff
  cal_dJcHat = MatrixXd::Zero(c, info.dof.joint);
  cal_dJmHat = MatrixXd::Zero(m, info.dof.joint);

  // ******************************

  // force
  cal_FcBarRef = VectorXd::Zero(c);
}
