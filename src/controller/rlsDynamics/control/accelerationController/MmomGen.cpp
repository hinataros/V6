#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::MmomGen(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd AC = MatrixXd::Zero(6, info.dof.all);
  AC <<
    model.all.MM.block(0,0,6,info.dof.all);

  MatrixXd JcM = MatrixXd::Zero(c, info.dof.all);
  JcM <<
    cal_PcM.transpose(), cal_JcM;
  MatrixXd dJcM = MatrixXd::Zero(c, info.dof.all);
  dJcM <<
    cal_dPcM.transpose(), cal_dJcM;

  MatrixXd ACBar = MatrixXd::Zero(6+c, info.dof.all);
  ACBar <<
    AC,
    JcM;

  MatrixXd dAC = MatrixXd::Zero(6, info.dof.all);
  dAC <<
    model.all.dMM.block(0,0,6,info.dof.all);

  MatrixXd dACBar = MatrixXd::Zero(6+c, info.dof.all);
  dACBar <<
    dAC,
    dJcM;

  VectorXd dqM = VectorXd::Zero(info.dof.all);
  dqM <<
    cal_VM,
    model.all.dth;

  VectorXd cal_dLCBarRef = VectorXd::Zero(6+c);
  cal_dLCBarRef.head(6) = cal_dLCRef;

  ddqRef = pInv(ACBar)*(cal_dLCBarRef - dACBar*dqM) + N(ACBar)*ddqD(config, info, model);

  // ddqRef = VectorXd::Zero(info.dof.all);

  return ddqRef;
}
