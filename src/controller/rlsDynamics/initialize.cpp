#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initialize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  Bc_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);
  Bm_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);

  cal_XB = Vector6d::Zero();
  cal_VB = Vector6d::Zero();
  cal_VM = Vector6d::Zero();
  cal_X = VectorXd::Zero(6*info.value.joint);
  cal_V = VectorXd::Zero(6*info.value.joint);

  // ******************************
  cal_J = MatrixXd::Zero(6*info.value.joint, info.dof.joint);
  bb_Rk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  TB2k = MatrixXd::Zero(6*info.value.joint, 6);

  // diff
  cal_dJ = MatrixXd::Zero(6*info.value.joint, info.dof.joint);
  bb_dRk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  dTB2k = MatrixXd::Zero(6*info.value.joint, 6);

  // ******************************
  TC2k = MatrixXd::Zero(6*info.value.joint, 6);

  // diff
  dTC2k = MatrixXd::Zero(6*info.value.joint, 6);
  // ******************************

  // rename
  // ******************************
  // inertia
  IB = Matrix3d::Zero();
  HBth = MatrixXd::Zero(6, info.dof.joint);
  Mth = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  // nonlinear
  cal_CB = Vector6d::Zero();
  cth = VectorXd::Zero(info.dof.joint);

  // gravity
  cal_GB = Vector6d::Zero();
  gth = VectorXd::Zero(info.dof.joint);

  // ******************************
  // inertia
  IC = Matrix3d::Zero();
  HC = MatrixXd::Zero(3, info.dof.joint);
  MthC = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  // diff inertia
  dIC = Matrix3d::Zero();
  dHC = MatrixXd::Zero(3, info.dof.joint);

  // nonlinear
  cal_CM = Vector6d::Zero();
  cthC = VectorXd::Zero(info.dof.joint);

  // gravity
  cal_GC = Vector6d::Zero();

  // ******************************
  rC0 = rCf = Vector3d::Zero();

  rB0 = rBf = Vector3d::Zero();
  xiB0 = xiBf = Vector3d::Zero();

  cal_X0 = VectorXd::Zero(6*info.value.joint);
  cal_Xf = VectorXd::Zero(6*info.value.joint);

  des = Vector3d::Zero();

  rCtemp = Vector3d::Zero();
  rBtemp = Vector3d::Zero();
  xiBtemp = Vector3d::Zero();
  cal_Xtemp = VectorXd::Zero(6*info.value.joint);

  rCDes = vCDes = dvCDes = Vector3d::Zero();

  rBDes = vBDes = dvBDes = Vector3d::Zero();

  xiBDes = dxiBDes = ddxiBDes = Vector3d::Zero();
  RBDes = Matrix3d::Zero();
  wBDes = dwBDes = Vector3d::Zero();
  cal_XDes = cal_VDes = cal_dVDes = VectorXd::Zero(6*info.value.joint);

  erC = evC = Vector3d::Zero();
  erB = evB = eoB = ewB = Vector3d::Zero();

  dvCRef = Vector3d::Zero();

  dvBRef = Vector3d::Zero();
  dwBRef = Vector3d::Zero();

  cal_dVBRef = Vector6d::Zero();
  cal_dVMRef = Vector6d::Zero();

  cal_dVRef = VectorXd::Zero(6*info.value.joint);

  h = VectorXd::Zero(info.dof.joint);

  // momentum
  cal_dLBRef = Vector6d::Zero();
  cal_dLCRef = Vector6d::Zero();

  ddthcRef = VectorXd::Zero(info.dof.joint);
  ddthmRef = VectorXd::Zero(info.dof.joint);
  ddthRef = VectorXd::Zero(info.dof.joint);

  tau = VectorXd::Zero(info.dof.joint);

  // gain
  kpC = 0.;
  kdC = 0.;

  kpvB = 0.;
  kdvB = 0.;

  kpwB = 0.;
  kdwB = 0.;
}
