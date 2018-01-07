/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initialize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  initialValueFlag = true;

  c = 0;
  m = 0;

  Bc_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);
  Bm_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);

  cal_XB = Vector6d::Zero();
  cal_VB = Vector6d::Zero();
  cal_VM = Vector6d::Zero();
  cal_VC = Vector6d::Zero();
  cal_X = VectorXd::Zero(6*info.value.joint);
  cal_V = VectorXd::Zero(6*info.value.joint);

  cal_F = VectorXd::Zero(6*info.value.joint);

  dq = VectorXd::Zero(info.dof.all);

  // ******************************
  cal_J = MatrixXd::Zero(6*info.value.joint, info.dof.joint);
  bb_Rk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  TB2k = MatrixXd::Zero(6*info.value.joint, 6);

  // diff
  cal_dJ = MatrixXd::Zero(6*info.value.joint, info.dof.joint);
  bb_dRk = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  dTB2k = MatrixXd::Zero(6*info.value.joint, 6);

  Jth = MatrixXd::Zero(6, info.dof.joint);
  dJth = MatrixXd::Zero(6, info.dof.joint);

  // ******************************
  TC2k = MatrixXd::Zero(6*info.value.joint, 6);

  // diff
  dTC2k = MatrixXd::Zero(6*info.value.joint, 6);
  // ******************************

  // rename
  // ******************************
  rB2C = Vector3d::Zero();
  drB2C = Vector3d::Zero();

  // inertia
  IB = Matrix3d::Zero();
  MB = Matrix6d::Zero();
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
  cthC = VectorXd::Zero(info.dof.joint);

  // gravity
  gf = Vector3d::Zero();
  cal_GC = Vector6d::Zero();

  // ******************************
  // inertia
  MthHat = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  // nonlinear
  cthHat = VectorXd::Zero(info.dof.joint);

  // index
  // ******************************
  // cop
  rpk = VectorXd::Zero(2*info.value.joint);
  rp = Vector2d::Zero();

  // cop
  wX = 0.;
  rX = Vector3d::Zero();

  // boundary
  // ******************************
  rC0 = rCf = Vector3d::Zero();

  rB0 = rBf = Vector3d::Zero();
  xiB0 = xiBf = Vector3d::Zero();

  cal_X0 = VectorXd::Zero(6*info.value.joint);
  cal_Xf = VectorXd::Zero(6*info.value.joint);

  cal_Fext0 = Vector6d::Zero();
  cal_Fextf = Vector6d::Zero();

  // previous state
  // ******************************
  rCpreState = vCpreState = Vector3d::Zero();
  rBpreState = vBpreState = Vector3d::Zero();
  xiBpreState = xiBpreState = Vector3d::Zero();
  cal_XpreState = cal_VpreState = VectorXd::Zero(6*info.value.joint);

  // previous desired value
  // ******************************
  rCpreDes = Vector3d::Zero();
  rBpreDes = Vector3d::Zero();
  xiBpreDes = Vector3d::Zero();
  cal_XpreDes = VectorXd::Zero(6*info.value.joint);
  cal_FextpreDes = Vector6d::Zero();

  // desired value
  // ******************************
  des = Vector3d::Zero();

  rCDes = vCDes = dvCDes = Vector3d::Zero();

  rBDes = vBDes = dvBDes = Vector3d::Zero();

  xiBDes = dxiBDes = ddxiBDes = Vector3d::Zero();
  RBDes = Matrix3d::Zero();
  wBDes = dwBDes = Vector3d::Zero();
  cal_XDes = cal_VxiDes = cal_dVxiDes = VectorXd::Zero(6*info.value.joint);
  cal_VDes = cal_dVDes = VectorXd::Zero(6*info.value.joint);

  cal_FextDes = Vector6d::Zero();

  // high gain control
  thDes = VectorXd::Zero(info.dof.joint);

  // error
  // ******************************
  erC = evC = Vector3d::Zero();
  erB = evB = eoB = ewB = Vector3d::Zero();
  cal_Ep = cal_Ev = VectorXd::Zero(6*info.value.joint);

  // reference
  // ******************************
  dvCRef = Vector3d::Zero();

  dvBRef = Vector3d::Zero();
  dwBRef = Vector3d::Zero();

  cal_dVBRef = Vector6d::Zero();
  cal_dVMRef = Vector6d::Zero();
  cal_dVCRef = Vector6d::Zero();

  cal_dVRef = VectorXd::Zero(6*info.value.joint);

  // momentum
  dpRef = Vector3d::Zero();
  dlCRef = Vector3d::Zero();
  dlBRef = Vector3d::Zero();
  cal_dLBRef = Vector6d::Zero();
  cal_dLCRef = Vector6d::Zero();

  cal_FextRef = Vector6d::Zero();

  // velocityController
  // **********************
  vCRef = Vector3d::Zero();

  vBRef = Vector3d::Zero();
  wBRef = Vector3d::Zero();

  cal_VBRef = Vector6d::Zero();
  cal_VMRef = Vector6d::Zero();

  cal_VRef = VectorXd::Zero(6*info.value.joint);
  // **********************

  dthRef = VectorXd::Zero(info.dof.joint);
  dqRef = VectorXd::Zero(info.dof.all);

  ddthRef = VectorXd::Zero(info.dof.joint);

  ddqRef = VectorXd::Zero(info.dof.all);

  tau = VectorXd::Zero(info.dof.joint);

  virtualInput = Vector6d::Zero();

  // gain
  KpC = Matrix3d::Zero();
  KdC = Matrix3d::Zero();

  KpvB = Matrix3d::Zero();
  KdvB = Matrix3d::Zero();

  KpwB = Matrix3d::Zero();
  KdwB = Matrix3d::Zero();

  Kpv = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  Kdv = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);

  KDlC = Matrix3d::Zero();
  KDth = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  KDq = MatrixXd::Zero(info.dof.all, info.dof.all);

  // high gain control
  KpHG = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  KdHG = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  // mapping
  map_motionController["baseVelocitySynergy"] = &RLS::RlsDynamics::baseVelocitySynergy;
  map_motionController["mixedVelocitySynergy"] = &RLS::RlsDynamics::mixedVelocitySynergy;

  map_motionController["baseAccelerationSynergy"] = &RLS::RlsDynamics::baseAccelerationSynergy;
  map_motionController["mixedAccelerationSynergy"] = &RLS::RlsDynamics::mixedAccelerationSynergy;
  map_motionController["centroidalAccelerationSynergy"] = &RLS::RlsDynamics::centroidalAccelerationSynergy;

  map_motionController["noname"] = &RLS::RlsDynamics::noname;
  map_motionController["baseGeneralizedMomentum"] = &RLS::RlsDynamics::baseGeneralizedMomentum;
  map_motionController["mixedGeneralizedMomentum"] = &RLS::RlsDynamics::mixedGeneralizedMomentum;

  map_momentumController["baseMomentum"] = &RLS::RlsDynamics::baseMomentum;
  map_momentumController["centroidalMomentum"] = &RLS::RlsDynamics::centroidalMomentum;

  map_forceController["baseDistribution"] = &RLS::RlsDynamics::baseDistribution;
  map_forceController["centroidalDistribution"] = &RLS::RlsDynamics::centroidalDistribution;

  map_torqueController["staticControl"] = &RLS::RlsDynamics::staticControl;
  map_torqueController["base"] = &RLS::RlsDynamics::base;
  map_torqueController["mixed"] = &RLS::RlsDynamics::mixed;
  map_torqueController["mixedmixed"] = &RLS::RlsDynamics::mixedmixed;
  map_torqueController["crb"] = &RLS::RlsDynamics::crb;

  map_inverseDynamicsController["fullDynamics"] = &RLS::RlsDynamics::fullDynamicsController;
  map_inverseDynamicsController["highGain"] = &RLS::RlsDynamics::highGainController;
}
