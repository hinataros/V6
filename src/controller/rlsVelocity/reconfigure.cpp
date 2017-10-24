#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::reconfigure(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  Bc = MatrixXd::Zero(6*info.value.joint, c);
  Bm = MatrixXd::Zero(6*info.value.joint, m);

  cal_Pc = MatrixXd::Zero(6, c);
  cal_Pm = MatrixXd::Zero(6, m);
  cal_Jc = MatrixXd::Zero(c, info.dof.joint);
  cal_Jm = MatrixXd::Zero(m, info.dof.joint);

  cal_PcM = MatrixXd::Zero(6, c);
  cal_PmM = MatrixXd::Zero(6, m);
  cal_JcM = MatrixXd::Zero(c, info.dof.joint);
  cal_JmM = MatrixXd::Zero(m, info.dof.joint);

  cal_VcBarRef = VectorXd::Zero(c);

  cal_VmBarRef = VectorXd::Zero(m);
  cal_VmTildeRef = VectorXd::Zero(m);
  cal_JmBar = MatrixXd::Zero(m, info.dof.joint);;
}
