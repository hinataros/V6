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

  // transform offset
  // rkk = new Vector3d[cnn];

  // for(int i=0; i<cnn; i++)
  //   rkk[i] = Vector3d::Zero();

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
  KDth = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);
  Kthinit = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);

  // high gain control
  KpHG = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);
  KdHG = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);

  // optimization weight
  Wdh = Matrix6d::Zero();
  Wm = MatrixXd::Zero(6*info.model.controlNodeNum, 6*info.model.controlNodeNum);
  WJ = MatrixXd::Zero(6*info.model.controlNodeNum, 6*info.model.controlNodeNum);

  Wth = MatrixXd::Zero(info.model.dof.joint, info.model.dof.joint);
  // smiyahara: 接触点の個数を数えたい
  Wp = MatrixXd::Zero(2*info.model.controlNodeNum, 2*info.model.controlNodeNum);
  WF = MatrixXd::Zero(6*info.model.controlNodeNum, 6*info.model.controlNodeNum);
  WFmin = MatrixXd::Zero(6*info.model.controlNodeNum, 6*info.model.controlNodeNum);

  // // high gain control
  thDes = VectorXd::Zero(info.model.dof.joint);

  sequence = new Sequence[yamlInfo.sequenceNum];
  for(int i=0; i<yamlInfo.sequenceNum; i++){
    sequence[i].phase = 0;
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
}
