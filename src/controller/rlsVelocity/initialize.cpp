#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::initialize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  Bc_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);
  Bm_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);

  cal_X = VectorXd::Zero(6*info.value.joint);
  cal_J = MatrixXd::Zero(6*info.value.joint, info.dof.joint);

  bb_Rk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  TB2k = MatrixXd::Zero(6*info.value.joint, 6);

  TC2k = MatrixXd::Zero(6*info.value.joint, 6);

  // rename
  IB = Matrix3d::Zero();
  HBth = MatrixXd::Zero(6, info.dof.joint);
  Mth = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  BJC = MatrixXd::Zero(3, info.dof.joint);

  // ******************************
  rB0 = xiB0 = Vector3d::Zero();
  rBf = xiBf = Vector3d::Zero();
  cal_X0 = VectorXd::Zero(6*info.value.joint);
  cal_Xf = VectorXd::Zero(6*info.value.joint);

  des = Vector3d::Zero();

  rCtemp = Vector3d::Zero();
  rBtemp = Vector3d::Zero();
  xiBtemp = Vector3d::Zero();
  cal_Xtemp = VectorXd::Zero(6*info.value.joint);

  rCDes = vCDes = Vector3d::Zero();
  rBDes = vBDes = Vector3d::Zero();
  xiBDes = dxiBDes = Vector3d::Zero();
  RBDes = Matrix3d::Zero();
  wBDes = Vector3d::Zero();
  cal_XDes = cal_VDes = VectorXd::Zero(6*info.value.joint);

  erC = Vector3d::Zero();
  erB = eoB = Vector3d::Zero();

  vCRef = Vector3d::Zero();

  vBRef = Vector3d::Zero();
  wBRef = Vector3d::Zero();

  cal_VBRef = Vector6d::Zero();
  cal_VMRef = Vector6d::Zero();

  cal_VRef = VectorXd::Zero(6*info.value.joint);

  dthcRef = VectorXd::Zero(info.dof.joint);
  dthmRef = VectorXd::Zero(info.dof.joint);
  dthRef = VectorXd::Zero(info.dof.joint);

  dqRef = VectorXd::Zero(info.dof.all);

  // gain
  kpC = 0.;

  kpvB = 0.;
  kpwB = 0.;
}
