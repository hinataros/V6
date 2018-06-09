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

  // smiyahara: model.worldとかに持ってきたい
  g = 9.81;

  Bc_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);
  Bm_kDiag = MatrixXi::Zero(6*info.value.joint, 6*info.value.joint);

  BpDiag = MatrixXi::Zero(2*info.value.joint, 2*info.value.joint);

  cal_XB = Vector6d::Zero();
  cal_VB = Vector6d::Zero();
  cal_VM = Vector6d::Zero();
  cal_VC = Vector6d::Zero();
  cal_X = VectorXd::Zero(6*info.value.joint);
  cal_V = VectorXd::Zero(6*info.value.joint);

  cal_F = VectorXd::Zero(6*info.value.joint);

  dq = VectorXd::Zero(info.dof.all);
  dqM = VectorXd::Zero(info.dof.all);

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
  cal_AB = MatrixXd::Zero(6, info.dof.all);
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
  MC = Matrix6d::Zero();
  HMth = MatrixXd::Zero(6, info.dof.joint);
  HC = MatrixXd::Zero(3, info.dof.joint);
  cal_AM = MatrixXd::Zero(6, info.dof.all);
  MthC = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  // diff inertia
  dIC = Matrix3d::Zero();
  dHC = MatrixXd::Zero(3, info.dof.joint);

  // nonlinear
  cal_CM = Vector6d::Zero();
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
  // smiyahara: 場所がビミョー
  bb_Spx = antiDiag(2, 1., -1.);

  // smiyahara: 場所がビミョー
  cal_Sp = MatrixXd::Zero(2, 6);
  cal_Sp.block(0,3,2,2) = bb_Spx;

  // CoP
  rpw2k = VectorXd::Zero(2*info.value.joint);
  rpk = VectorXd::Zero(2*info.value.joint);
  rp = Vector2d::Zero();

  // CMP
  rcmp = Vector2d::Zero();

  // DCM
  wX = 0.;
  rX = Vector3d::Zero();

  // boundary
  // ******************************
  rC0 = rCf = Vector3d::Zero();

  rB0 = rBf = Vector3d::Zero();
  xiB0 = xiBf = Vector3d::Zero();

  rX0 = rXf = Vector3d::Zero();

  cal_X0 = VectorXd::Zero(6*info.value.joint);
  cal_Xf = VectorXd::Zero(6*info.value.joint);

  cal_Fext0 = Vector6d::Zero();
  cal_Fextf = Vector6d::Zero();

  rpk0 = VectorXd::Zero(2*info.value.joint);

  // previous state
  // ******************************
  rCpreState = vCpreState = Vector3d::Zero();
  rBpreState = vBpreState = Vector3d::Zero();
  xiBpreState = xiBpreState = Vector3d::Zero();

  rXpreState = drXpreState = Vector3d::Zero();
  cal_XpreState = cal_VpreState = VectorXd::Zero(6*info.value.joint);

  // previous desired value
  // ******************************
  rCpreDes = Vector3d::Zero();
  rBpreDes = Vector3d::Zero();
  xiBpreDes = Vector3d::Zero();
  rXpreDes = Vector3d::Zero();
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

  rXDes = drXDes = Vector3d::Zero();

  cal_XDes = cal_VxiDes = cal_dVxiDes = VectorXd::Zero(6*info.value.joint);
  cal_VDes = cal_dVDes = VectorXd::Zero(6*info.value.joint);

  cal_FextDes = Vector6d::Zero();

  // high gain control
  thDes = VectorXd::Zero(info.dof.joint);

  // dcmWalkiing
  // ******************************
  phaseDS = 0;
  flagDS = true;

  stepNum = 10;
  stepPhase = 0;
  tstep0 = 0.;
  tstep = 0.;
  tDS0 = 0.;

  dt = VectorXd::Zero(stepNum);
  rf = MatrixXd::Zero(3,stepNum);
  rvrpd = MatrixXd::Zero(3,stepNum+1);

  rXeos = MatrixXd::Zero(3,stepNum+1);

  // double sopport
  dtDS = VectorXd::Zero(stepNum+1);
  alphDS = VectorXd::Zero(stepNum+1);
  dtDSini = VectorXd::Zero(stepNum+1);
  dtDSend = VectorXd::Zero(stepNum+1);

  rXiniDS = MatrixXd::Zero(3,stepNum+1);
  rXeoDS = MatrixXd::Zero(3,stepNum+1);
  drXiniDS = MatrixXd::Zero(3,stepNum+1);
  drXeoDS = MatrixXd::Zero(3,stepNum+1);
  ddrXiniDS = MatrixXd::Zero(3,stepNum+1);
  ddrXeoDS = MatrixXd::Zero(3,stepNum+1);

  // ******************************

  // dcmWalkiing
  // // 3step
  // // ******************************
  // dt = VectorXd::Zero(3);
  // rf = MatrixXd::Zero(3,3);
  // rvrpd = MatrixXd::Zero(3,4);

  // rXeos = MatrixXd::Zero(3,4);

  // // double sopport
  // dtDS = VectorXd::Zero(4);
  // alphDS = VectorXd::Zero(4);
  // dtDSini = VectorXd::Zero(4);
  // dtDSend = VectorXd::Zero(4);

  // rXiniDS = MatrixXd::Zero(3,4);
  // rXeoDS = MatrixXd::Zero(3,4);
  // drXiniDS = MatrixXd::Zero(3,4);
  // drXeoDS = MatrixXd::Zero(3,4);
  // ddrXiniDS = MatrixXd::Zero(3,4);
  // ddrXeoDS = MatrixXd::Zero(3,4);

  // // ******************************

  // error
  // ******************************
  erC = evC = Vector3d::Zero();
  erB = evB = eoB = ewB = Vector3d::Zero();
  cal_Ep = cal_Ev = VectorXd::Zero(6*info.value.joint);

  // reference
  // ******************************
  // velocityController
  // **********************
  vBRef = Vector3d::Zero();
  wBRef = Vector3d::Zero();
  dthRef = VectorXd::Zero(info.dof.joint);

  dqBRef = VectorXd::Zero(info.dof.all);

  vCRef = Vector3d::Zero();

  dqMRef = VectorXd::Zero(info.dof.all);

  cal_VBRef = Vector6d::Zero();
  cal_VMRef = Vector6d::Zero();

  cal_VRef = VectorXd::Zero(6*info.value.joint);
  // **********************

  dvBRef = Vector3d::Zero();
  dwBRef = Vector3d::Zero();
  ddthRef = VectorXd::Zero(info.dof.joint);

  ddqBRef = VectorXd::Zero(info.dof.all);
  ddqBoptRef = VectorXd::Zero(info.dof.all);

  dvCRef = Vector3d::Zero();

  ddqMRef = VectorXd::Zero(info.dof.all);
  ddqMoptRef = VectorXd::Zero(info.dof.all);

  drXRef = Vector3d::Zero();

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

  tau = VectorXd::Zero(info.dof.joint);

  virtualInput = Vector6d::Zero();

  // gain
  KpC = Matrix3d::Zero();
  KdC = Matrix3d::Zero();

  KpvB = Matrix3d::Zero();
  KdvB = Matrix3d::Zero();

  KpwB = Matrix3d::Zero();
  KdwB = Matrix3d::Zero();

  KX = Matrix3d::Zero();

  Kpv = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  Kdv = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);

  Kpp = Matrix2d::Zero();

  KDlC = Matrix3d::Zero();
  KDth = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  KDq = MatrixXd::Zero(info.dof.all, info.dof.all);

  // high gain control
  KpHG = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  KdHG = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  // optimization weight
  WFSD = Matrix6d::Zero();
  Wm = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);
  WJ = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);

  Wth = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  // smiyahara: 接触点の個数を数えたい
  Wp = MatrixXd::Zero(2*info.value.joint, 2*info.value.joint);
  WF = MatrixXd::Zero(6*info.value.joint, 6*info.value.joint);

  // trigger flag
  flagInit = true;
  flagHip = false;
  flagStay = false;

  // selective matrix for forward kinematics
  bb_ScB = Matrix6d::Zero();

  motionControllerName =
    momentumControllerName =
    forceControllerName =
    torqueControllerName =
    inverseDynamicsControllerName = "default";

  // mapping
  map_momentumController["default"] = &RLS::RlsDynamics::zeroMomentum;
  map_momentumController["baseMomentum"] = &RLS::RlsDynamics::baseMomentum;
  map_momentumController["centroidalMomentum"] = &RLS::RlsDynamics::centroidalMomentum;
  map_momentumController["centroidalDcmMomentum"] = &RLS::RlsDynamics::centroidalDcmMomentum;
  map_momentumController["centroidalCmpMomentum"] = &RLS::RlsDynamics::centroidalCmpMomentum;

  map_motionController["default"] = &RLS::RlsDynamics::zeroMotion;
  map_motionController["baseVelocitySynergy"] = &RLS::RlsDynamics::baseVelocitySynergy;
  map_motionController["mixedVelocitySynergy"] = &RLS::RlsDynamics::mixedVelocitySynergy;

  map_motionController["workAcceleration"] = &RLS::RlsDynamics::workAcceleration;
  map_motionController["baseAccelerationSynergy"] = &RLS::RlsDynamics::baseAccelerationSynergy;
  map_motionController["mixedAccelerationSynergy"] = &RLS::RlsDynamics::mixedAccelerationSynergy;
  map_motionController["centroidalAccelerationSynergy"] = &RLS::RlsDynamics::centroidalAccelerationSynergy;
  map_motionController["hinata"] = &RLS::RlsDynamics::hinata;

  map_motionController["noname"] = &RLS::RlsDynamics::noname;
  map_motionController["baseGeneralizedMomentum"] = &RLS::RlsDynamics::baseGeneralizedMomentum;
  map_motionController["mixedGeneralizedMomentum"] = &RLS::RlsDynamics::mixedGeneralizedMomentum;
  map_motionController["accelerationSolver"] = &RLS::RlsDynamics::accelerationSolver;

  map_forceController["default"] = &RLS::RlsDynamics::zeroDistribution;
  map_forceController["baseDistribution"] = &RLS::RlsDynamics::baseDistribution;
  map_forceController["centroidalDistribution"] = &RLS::RlsDynamics::centroidalDistribution;
  map_forceController["centroidalDcmDistribution"] = &RLS::RlsDynamics::centroidalDcmDistribution;
  map_forceController["distributionSolver"] = &RLS::RlsDynamics::distributionSolver;

  map_torqueController["default"] = &RLS::RlsDynamics::zeroTorque;
  map_torqueController["jointSpace"] = &RLS::RlsDynamics::jointSpace;
  map_torqueController["staticControl"] = &RLS::RlsDynamics::staticControl;
  map_torqueController["base"] = &RLS::RlsDynamics::base;
  map_torqueController["mixed"] = &RLS::RlsDynamics::mixed;
  map_torqueController["mixedmixed"] = &RLS::RlsDynamics::mixedmixed;
  map_torqueController["crb"] = &RLS::RlsDynamics::crb;
  map_torqueController["baseOpt"] = &RLS::RlsDynamics::baseOpt;
  map_torqueController["mixedOpt"] = &RLS::RlsDynamics::mixedOpt;
  map_torqueController["mixedmixedOpt"] = &RLS::RlsDynamics::mixedmixedOpt;

  map_inverseDynamicsController["default"] = &RLS::RlsDynamics::zeroDynamics;
  map_inverseDynamicsController["fullDynamics"] = &RLS::RlsDynamics::fullDynamicsController;
  map_inverseDynamicsController["momentumInverseDynamics"] = &RLS::RlsDynamics::momentumInverseDynamicsController;
  map_inverseDynamicsController["highGain"] = &RLS::RlsDynamics::highGainController;
  map_inverseDynamicsController["spatialDynamicsSolver"] = &RLS::RlsDynamics::spatialDynamicsSolver;
  map_inverseDynamicsController["atlasSolver"] = &RLS::RlsDynamics::atlasSolver;
}
