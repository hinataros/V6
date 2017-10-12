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
  cal_X = VectorXd::Zero(6*info.value.joint);
  cal_V = VectorXd::Zero(6*info.value.joint);

  cal_J = MatrixXd::Zero(6*info.value.joint, info.dof.joint);
  bb_Rk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  bb_Tk2B = MatrixXd::Zero(6*info.value.joint, 6);

  // diff
  cal_dJ = MatrixXd::Zero(6*info.value.joint, info.dof.joint);
  bb_dRk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  bb_dTk2B = MatrixXd::Zero(6*info.value.joint, 6);

  // rename
  dq = VectorXd::Zero(info.dof.all);
  IB = Matrix3d::Zero();
  HBth = MatrixXd::Zero(6, info.dof.joint);
  Mth = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  cal_AB = MatrixXd::Zero(6, info.dof.all);
  cal_dAB = MatrixXd::Zero(6, info.dof.all);
  cB = Vector6d::Zero();
  cth = VectorXd::Zero(info.dof.joint);
  gB = Vector6d::Zero();
  gth = VectorXd::Zero(info.dof.joint);

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

  ddthcRef = VectorXd::Zero(info.dof.joint);
  ddthmRef = VectorXd::Zero(info.dof.joint);
  ddthRef = VectorXd::Zero(info.dof.joint);

  ddqRef = VectorXd::Zero(info.dof.all);

  tau = VectorXd::Zero(info.dof.joint);

  // gain
  kpC = 0.;
  kdC = 0.;

  kpvB = 0.;
  kdvB = 0.;

  kpwB = 0.;
  kdwB = 0.;
}
