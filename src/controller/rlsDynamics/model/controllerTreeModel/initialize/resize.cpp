/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::resize()
{
  if(debug) DEBUG;

  th0 = VectorXd::Zero(info->dof.joint);
  rB0 = Vector3d::Zero();
  RB0 = Matrix3d::Zero();
  r0 = new Vector3d[info->controlNodeNum];
  R0 = new Matrix3d[info->controlNodeNum];

  for(int i=0; i<info->controlNodeNum; i++){
    r0[i] = Vector3d::Zero();
    R0[i] = Matrix3d::Zero();
  }

  rC0 = Vector3d::Zero();
  rX0 = Vector3d::Zero();
  cal_FB0 = Vector6d::Zero();

  rpk0 = VectorXd::Zero(2*info->controlNodeNum);

  th = VectorXd::Zero(info->dof.joint);
  dth = VectorXd::Zero(info->dof.joint);

  rB = Vector3d::Zero();
  RB = Matrix3d::Zero();
  vB = Vector3d::Zero();
  wB = Vector3d::Zero();

  wC = Vector3d::Zero(); //amiyata

  rC = Vector3d::Zero();
  vC = Vector3d::Zero();

  cal_VB = Vector6d::Zero();
  cal_VM = Vector6d::Zero();
  cal_VC = Vector6d::Zero();

  r = new Vector3d[info->controlNodeNum];
  R = new Matrix3d[info->controlNodeNum];

  for(int i=0; i<info->controlNodeNum; i++){
    r[i] = Vector3d::Zero();
    R[i] = Matrix3d::Zero();
  }

  cal_V = VectorXd::Zero(6*info->controlNodeNum);
  cal_F = VectorXd::Zero(6*info->controlNodeNum);

  rsensor = new Vector3d[info->sensorNodeNum];
  for(int i=0; i<info->sensorNodeNum; i++){
    rsensor[i] = Vector3d::Zero();
  }
  cal_Fsensor = VectorXd::Zero(6*info->sensorNodeNum);

  dq = VectorXd::Zero(info->dof.all);
  dqM = VectorXd::Zero(info->dof.all);

  M = 0.;

  bb_Rk = MatrixXd::Zero(6*info->controlNodeNum, 6*info->controlNodeNum);
  bb_dRk = MatrixXd::Zero(6*info->controlNodeNum, 6*info->controlNodeNum);

  bb_TB2k = MatrixXd::Zero(6*info->controlNodeNum, 6);
  bb_dTB2k = MatrixXd::Zero(6*info->controlNodeNum, 6);
  bb_TC2k = MatrixXd::Zero(6*info->controlNodeNum, 6);
  bb_dTC2k = MatrixXd::Zero(6*info->controlNodeNum, 6);

  cal_J = MatrixXd::Zero(6*info->controlNodeNum, info->dof.joint);
  cal_dJ = MatrixXd::Zero(6*info->controlNodeNum, info->dof.joint);

  JB2C = MatrixXd::Zero(3, info->dof.joint);
  dJB2C = MatrixXd::Zero(3, info->dof.joint);

  Jth = MatrixXd::Zero(6, info->dof.joint);
  dJth = MatrixXd::Zero(6, info->dof.joint);

  // rename
  // ******************************
  rB2C = Vector3d::Zero();
  drB2C = Vector3d::Zero();

  // inertia
  IB = Matrix3d::Zero();
  MB = Matrix6d::Zero();
  HBth = MatrixXd::Zero(6, info->dof.joint);
  cal_AB = MatrixXd::Zero(6, info->dof.all);
  Mth = MatrixXd::Zero(info->dof.joint, info->dof.joint);

  // nonlinear
  cal_dAB = MatrixXd::Zero(6, info->dof.all);
  cal_CB = Vector6d::Zero();
  cth = VectorXd::Zero(info->dof.joint);

  // gravity
  cal_GB = Vector6d::Zero();
  gth = VectorXd::Zero(info->dof.joint);

  // ******************************
  // inertia
  IC = Matrix3d::Zero();
  MC = Matrix6d::Zero();
  HMth = MatrixXd::Zero(6, info->dof.joint);
  HC = MatrixXd::Zero(3, info->dof.joint);
  cal_AM = MatrixXd::Zero(6, info->dof.all);
  MthC = MatrixXd::Zero(info->dof.joint, info->dof.joint);

  Jw = MatrixXd::Zero(3, info->dof.joint); //amiyata

  // diff inertia
  cal_dAM = MatrixXd::Zero(6, info->dof.all);
  dIC = Matrix3d::Zero();
  dHC = MatrixXd::Zero(3, info->dof.joint);

  dJw = MatrixXd::Zero(3, info->dof.joint); //amiyata

  // nonlinear
  cmm = Vector3d::Zero();
  cal_CM = Vector6d::Zero();
  cthC = VectorXd::Zero(info->dof.joint);

  // gravity
  gf = Vector3d::Zero();
  cal_GC = Vector6d::Zero();

  // ******************************
  // inertia
  MthHat = MatrixXd::Zero(info->dof.joint, info->dof.joint);

  // nonlinear
  cthHat = VectorXd::Zero(info->dof.joint);

  // index
  // ******************************
  // CoP
  rpw2k = VectorXd::Zero(2*info->sensorNodeNum);
  rpk = VectorXd::Zero(2*info->sensorNodeNum);
  rp = Vector2d::Zero();

  // CMP
  rcmp = Vector2d::Zero();

  // DCM
  wX = 0.;
  rX = Vector3d::Zero();
}
