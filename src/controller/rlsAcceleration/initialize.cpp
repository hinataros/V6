#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsAcceleration.hpp"

void RLS::RlsAcceleration::initialize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  Bc_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);
  Bm_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);

  cal_VB = Vector6d::Zero();
  cal_X = VectorXd::Zero(6*info.value.joint);
  cal_V = VectorXd::Zero(6*info.value.joint);

  cal_J = MatrixXd::Zero(6*info.value.joint, info.dof.joint);
  bb_Rk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  bb_Tk2B = MatrixXd::Zero(6*info.value.joint, 6);

  // diff
  cal_dJ = MatrixXd::Zero(6*info.value.joint, info.dof.joint);
  bb_dRk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  bb_dTk2B = MatrixXd::Zero(6*info.value.joint, 6);

  rB0 = xiB0 = Vector3d::Zero();
  rBf = xiBf = Vector3d::Zero();
  cal_X0 = VectorXd::Zero(6*info.value.joint);
  cal_Xf = VectorXd::Zero(6*info.value.joint);

  des = Vector3d::Zero();

  rBtemp = Vector3d::Zero();
  xiBtemp = Vector3d::Zero();
  cal_Xtemp = VectorXd::Zero(6*info.value.joint);

  rBDes = vBDes = dvBDes = Vector3d::Zero();
  xiBDes = dxiBDes = ddxiBDes = Vector3d::Zero();
  RBDes = Matrix3d::Zero();
  wBDes = dwBDes = Vector3d::Zero();
  cal_XDes = cal_VDes = cal_dVDes = VectorXd::Zero(6*info.value.joint);

  erB = evB = eoB = ewB = Vector3d::Zero();

  dvBRef = Vector3d::Zero();
  dwBRef = Vector3d::Zero();
  cal_dVBRef = Vector6d::Zero();

  cal_dVRef = VectorXd::Zero(6*info.value.joint);

  h = VectorXd::Zero(info.dof.joint);

  ddthcRef = VectorXd::Zero(info.dof.joint);
  ddthmRef = VectorXd::Zero(info.dof.joint);
  ddthRef = VectorXd::Zero(info.dof.joint);

  ddqRef = VectorXd::Zero(info.dof.all);

  kpvB = 0.;
  kpwB = 0.;
  kdvB = 0.;
  kdwB = 0.;
}
