/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initialize(const Config &config, const TreeModel::Info &info)
{
  if(debug) DEBUG;

  initialValueFlag = true;

  dt = 0.;
  // smiyahara: model.worldとかに持ってきたい
  g = 9.81;

  Bc_kDiag = MatrixXi::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);
  Bm_kDiag = MatrixXi::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);

  BpDiag = MatrixXi::Zero(2*info.controlNodeNum, 2*info.controlNodeNum);

  th = VectorXd::Zero(info.dof.joint);
  dth = VectorXd::Zero(info.dof.joint);

  rB = Vector3d::Zero();
  xiB = Vector3d::Zero();
  vB = Vector3d::Zero();
  wB = Vector3d::Zero();

  rC = Vector3d::Zero();
  vC = Vector3d::Zero();

  cal_XB = Vector6d::Zero();
  cal_VB = Vector6d::Zero();
  cal_VM = Vector6d::Zero();
  cal_VC = Vector6d::Zero();
  cal_X = VectorXd::Zero(6*info.controlNodeNum);
  cal_V = VectorXd::Zero(6*info.controlNodeNum);
  cal_F = VectorXd::Zero(6*info.controlNodeNum);

  // cal_Xsensor = VectorXd::Zero(6*info.sensorNodeNum);
  // cal_Fsensor = VectorXd::Zero(6*info.sensorNodeNum);

  dq = VectorXd::Zero(info.dof.all);
  dqM = VectorXd::Zero(info.dof.all);

  M = 0.;
  ag = Vector3d::Zero();
  JB2C = MatrixXd::Zero(3, info.dof.joint);
  dJB2C = MatrixXd::Zero(3, info.dof.joint);

  // transform offset
  rkk = new Vector3d[info.controlNodeNum];

  for(int i=0; i<info.controlNodeNum; i++)
    rkk[i] = Vector3d::Zero();

  bb_Rk = MatrixXd::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);

  // diff
  bb_dRk = MatrixXd::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);

  Jth = MatrixXd::Zero(6, info.dof.joint);
  dJth = MatrixXd::Zero(6, info.dof.joint);

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
  cal_dAB = MatrixXd::Zero(6, info.dof.all);
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
  cal_dAM = MatrixXd::Zero(6, info.dof.all);
  dIC = Matrix3d::Zero();
  dHC = MatrixXd::Zero(3, info.dof.joint);

  // nonlinear
  cmm = Vector3d::Zero();
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
  rpw2k = VectorXd::Zero(2*info.controlNodeNum);
  rpk = VectorXd::Zero(2*info.controlNodeNum);
  rp = Vector2d::Zero();

  // CMP
  rcmp = Vector2d::Zero();

  // DCM
  wX = 0.;
  rX = Vector3d::Zero();

  // boundary
  // ******************************
  th0 = VectorXd::Zero(info.dof.joint);

  rC0 = Vector3d::Zero();

  rB0 = Vector3d::Zero();
  xiB0 = Vector3d::Zero();

  rX0 = Vector3d::Zero();

  cal_X0 = VectorXd::Zero(6*info.controlNodeNum);

  cal_Fext0 = Vector6d::Zero();

  rpk0 = VectorXd::Zero(2*info.controlNodeNum);

  // desired value
  // ******************************
  des = Vector3d::Zero();

  rCDes = vCDes = dvCDes = Vector3d::Zero();

  rBDes = vBDes = dvBDes = Vector3d::Zero();

  xiBDes = dxiBDes = ddxiBDes = Vector3d::Zero();
  RBDes = Matrix3d::Zero();
  wBDes = dwBDes = Vector3d::Zero();

  rXDes = drXDes = Vector3d::Zero();

  cal_XDes = cal_VxiDes = cal_dVxiDes = VectorXd::Zero(6*info.controlNodeNum);
  cal_VDes = cal_dVDes = VectorXd::Zero(6*info.controlNodeNum);

  cal_FextDes = Vector6d::Zero();

  // high gain control
  thDes = VectorXd::Zero(info.dof.joint);

  // error
  // ******************************
  erC = evC = Vector3d::Zero();
  erB = evB = eoB = ewB = Vector3d::Zero();
  cal_Ep = cal_Ev = VectorXd::Zero(6*info.controlNodeNum);

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

  cal_VRef = VectorXd::Zero(6*info.controlNodeNum);
  // **********************

  dvBRef = Vector3d::Zero();
  dwBRef = Vector3d::Zero();
  ddthRef = VectorXd::Zero(info.dof.joint);

  ddqBRef = VectorXd::Zero(info.dof.all);
  ddqBoptRef = VectorXd::Zero(info.dof.all);

  dvCRef = Vector3d::Zero();

  ddqMRef = VectorXd::Zero(info.dof.all);
  ddqMoptRef = VectorXd::Zero(info.dof.all);

  ddqwoptRef = VectorXd::Zero(3+info.dof.joint);

  drXRef = Vector3d::Zero();

  cal_dVBRef = Vector6d::Zero();
  cal_dVMRef = Vector6d::Zero();
  cal_dVCRef = Vector6d::Zero();

  cal_dVRef = VectorXd::Zero(6*info.controlNodeNum);

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

  Kpv = MatrixXd::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);
  Kdv = MatrixXd::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);

  Kpp = Matrix2d::Zero();

  KDlC = Matrix3d::Zero();
  KDth = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  Kthinit = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  // high gain control
  KpHG = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  KdHG = MatrixXd::Zero(info.dof.joint, info.dof.joint);

  // optimization weight
  Wdh = Matrix6d::Zero();
  Wm = MatrixXd::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);
  WJ = MatrixXd::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);

  Wth = MatrixXd::Zero(info.dof.joint, info.dof.joint);
  // smiyahara: 接触点の個数を数えたい
  Wp = MatrixXd::Zero(2*info.controlNodeNum, 2*info.controlNodeNum);
  WF = MatrixXd::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);
  WFmin = MatrixXd::Zero(6*info.controlNodeNum, 6*info.controlNodeNum);

  // trigger flag
  flagInit = true;
  flagHip = false;
  flagStay = false;

  // selective matrix for forward kinematics
  bb_ScB = Matrix6d::Zero();

  initializeState(info);
  initializeSequence(config.dir.work, info);
  initializeWalking(info);
  initializeTrajectoryGeneratorMap(info);
  initializeReferenceMap();
  initializeControllerMap();
  initializeTriggerMap(config.controller.trigger);
}
