#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::noname(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // MatrixXd cal_HCBar = MatrixXd::Zero(3+c, info.dof.joint);
  // cal_HCBar <<
  //   HC,
  //   cal_JcM;
  // MatrixXd cal_dHCBar = MatrixXd::Zero(3+c, info.dof.joint);
  // cal_dHCBar <<
  //   dHC,
  //   cal_dJcM;

  // MatrixXd MCBar = MatrixXd::Zero(3+c, 6);
  // MCBar <<
  //   Matrix3d::Zero(), IC,
  //   Pcf.transpose(), PcMm.transpose();
  // MatrixXd dMCBar = MatrixXd::Zero(3+c, 6);
  // dMCBar <<
  //   Matrix3d::Zero(), dIC,
  //   dPcf.transpose(), dPcMm.transpose();

  // VectorXd dlCBar = VectorXd::Zero(3+c);
  // dlCBar <<
  //   -0*model.all.lC,
  //   VectorXd::Zero(c);

  // // nonlinear term
  // VectorXd cM = dMCBar*cal_VM - cal_dHCBar*model.all.dth;

  // ddthRef = pInv(cal_HCBar)*(MCBar*cal_dVMRef - cM + dlCBar) + N(cal_HCBar)*ddthD(config, model);

  ddqRef = VectorXd::Zero(info.dof.all);

  return ddqRef;
}
