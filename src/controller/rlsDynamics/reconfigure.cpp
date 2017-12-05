#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reconfigure(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

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
  cal_JcM = MatrixXd::Zero(c, info.dof.joint);

  // diff
  dPcf = MatrixXd::Zero(3, c);
  dPcMm = MatrixXd::Zero(3, c);
  cal_dPcM = MatrixXd::Zero(6, c);
  cal_dJcM = MatrixXd::Zero(c, info.dof.joint);

  // ******************************

  // force
  cal_FcBarRef = VectorXd::Zero(c);
  cal_FcMBarRef = VectorXd::Zero(c);
}
