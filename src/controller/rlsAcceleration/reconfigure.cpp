#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsAcceleration.hpp"

void RLS::RlsAcceleration::reconfigure(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  Bc = MatrixXd::Zero(6*info.value.joint, c);
  Bm = MatrixXd::Zero(6*info.value.joint, m);

  cal_Pc = MatrixXd::Zero(6, c);
  cal_Pm = MatrixXd::Zero(6, m);

  cal_Jc = MatrixXd::Zero(c, info.dof.joint);
  cal_Jm = MatrixXd::Zero(m, info.dof.joint);

  // diff
  dBc = MatrixXd::Zero(6*info.value.joint, c);
  dBm = MatrixXd::Zero(6*info.value.joint, m);

  cal_dPc = MatrixXd::Zero(6, c);
  cal_dPm = MatrixXd::Zero(6, m);

  cal_dJc = MatrixXd::Zero(c, info.dof.joint);
  cal_dJm = MatrixXd::Zero(m, info.dof.joint);

  cal_dVcBarRef = VectorXd::Zero(c);

  cal_dVmBarRef = VectorXd::Zero(m);
  cal_dVmTildeRef = VectorXd::Zero(m);
  cal_JmBar = MatrixXd::Zero(m, info.dof.joint);;

  hc = VectorXd::Zero(c);
  hm = VectorXd::Zero(m);
}
