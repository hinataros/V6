/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::resize()
{
  if(debug) DEBUG;

  // smiyahara: 場所は要検討
  bb_Spx = antiDiag(2, 1., -1.);

  // smiyahara: 場所は要検討
  cal_Sp = MatrixXd::Zero(2, 6);
  cal_Sp.block(0,3,2,2) = bb_Spx;

  dthRef = VectorXd::Zero(info.model.dof.joint);
  dqBRef = VectorXd::Zero(info.model.dof.all);
  dqMRef = VectorXd::Zero(info.model.dof.all);

  ddthRef = VectorXd::Zero(info.model.dof.joint);

  ddqBRef = VectorXd::Zero(info.model.dof.all);
  ddqBoptRef = VectorXd::Zero(info.model.dof.all);

  ddqMRef = VectorXd::Zero(info.model.dof.all);
  ddqMoptRef = VectorXd::Zero(info.model.dof.all);

  ddqwoptRef = VectorXd::Zero(3+info.model.dof.joint);

  // momentum
  dpRef = Vector3d::Zero();
  dlCRef = Vector3d::Zero();
  dlBRef = Vector3d::Zero();
  cal_dLBRef = Vector6d::Zero();
  cal_dLCRef = Vector6d::Zero();

  tau = VectorXd::Zero(info.model.dof.joint);

  virtualInput = Vector6d::Zero();

  Kpp = Matrix2d::Zero();

  KDlC = Matrix3d::Zero();
  KDwC = Matrix3d::Zero();
  KDth = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);
  KPth = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint); // hinata
  KDdthH = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);
  KDlCH = MatrixXd::Zero(3,3);
  Kthinit = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);

  // high gain control
  KpHG = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);
  KdHG = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);

  // optimization weight // 2019/07/05 amiyata weightはデフォルトで1.0
  Wdh = Matrix6d::Identity();
  Wm = MatrixXd::Identity(6*info.model.controlNodeNum, 6*info.model.controlNodeNum);
  WJ = MatrixXd::Identity(6*info.model.controlNodeNum, 6*info.model.controlNodeNum);

  Wth = MatrixXd::Identity(info.model.dof.joint, info.model.dof.joint);
  // smiyahara: 接触点の個数を数えたい
  Wp = MatrixXd::Identity(2*info.model.controlNodeNum, 2*info.model.controlNodeNum);
  WF = MatrixXd::Identity(6*info.model.controlNodeNum, 6*info.model.controlNodeNum);
  WFmin = MatrixXd::Identity(6*info.model.controlNodeNum, 6*info.model.controlNodeNum);

  // // high gain control
  thDes = VectorXd::Zero(info.model.dof.joint);

  // amiyata
  BwB_Diag = MatrixXi::Zero(3,3);
  BLC_Diag = MatrixXi::Zero(6,6);
  BwC_Diag = MatrixXi::Zero(3,3);

  // amiyata rkk
  rkk = VectorXd::Zero(3*info.model.controlNodeNum);

  distOffset = Vector2d::Zero();

  sequence = new Sequence[yamlInfo.sequenceNum];
  for(int i=0; i<yamlInfo.sequenceNum; i++){
    sequence[i].phase = -1; // 初期phaseがややこしい
    sequence[i].tw0 = 0.;
    sequence[i].twf = 0.;
  }

  extMotionController =
    extMomentumController =
    extForceController =
    extTorqueController =
    extInverseDynamicsController =
    extExternalWrenchController = false;

  operationalSpaceControllerName =
    motionControllerName =
    momentumControllerName =
    internalForceControllerName =
    forceControllerName =
    torqueControllerName =
    inverseDynamicsControllerName = "default";

  externalWrenchControllerName = "default";

  // amiyata
  extractor.resize();
}
