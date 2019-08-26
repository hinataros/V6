/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::resize()
{
  if(debug) DEBUG;

  tw0 = new double[yamlInfo->sequenceNum];
  twf = new double[yamlInfo->sequenceNum];

  for(int i=0; i<yamlInfo->sequenceNum; i++){
    tw0[i] = 0.;
    twf[i] = 0.;
  }

  rCDes = vCDes = dvCDes = Vector3d::Zero();

  rBDes = vBDes = dvBDes = Vector3d::Zero();
  qBDes = dqBDes = ddqBDes = Quaternion4d::Zero();
  RBDes = Matrix3d::Zero();
  wBDes = dwBDes = Vector3d::Zero();

  rXDes = drXDes = Vector3d::Zero();

  rDes = new Vector3d[info->controlNodeNum];

  qDes = new Quaternion4d[info->controlNodeNum];
  dqDes = new Quaternion4d[info->controlNodeNum];
  ddqDes = new Quaternion4d[info->controlNodeNum];
  RDes = new Matrix3d[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    rDes[i] = Vector3d::Zero();

    qDes[i] = dqDes[i] = ddqDes[i] = Quaternion4d::Zero();
    RDes[i] = Matrix3d::Zero();
  }

  cal_VDes = cal_dVDes = VectorXd::Zero(6*info->controlNodeNum);

  cal_FDes = VectorXd::Zero(6*info->controlNodeNum);

  cal_FextDes = Vector6d::Zero();

  rB0 = Vector3d::Zero();
  qB0 = Quaternion4d::Zero();
  r0 = new Vector3d[info->controlNodeNum];
  q0 = new Quaternion4d[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    r0[i] = Vector3d::Zero();
    q0[i] = Quaternion4d::Zero();
  }
  rC0 = Vector3d::Zero();
  rX0 = Vector3d::Zero();
  cal_Fext0 = Vector6d::Zero();

  rBpreDes = Vector3d::Zero();
  qBpreDes = Quaternion4d::Zero();
  rCpreDes = Vector3d::Zero();
  rXpreDes = Vector3d::Zero();
  rXpreDesabs = Vector3d::Zero();
  cal_FextpreDes = Vector6d::Zero();
  // amiyata
  rBfinCur = Vector3d::Zero();
  qBfinCur = Quaternion4d::Zero();
  rCfinCur = Vector3d::Zero();
  rXfinCur = Vector3d::Zero();
  rXfinCurabs = Vector3d::Zero();
  // cal_FextfinCur = Vector6d::Zero();

  rBf = Vector3d::Zero();
  xiBf = Vector3d::Zero();
  qBf = Quaternion4d::Identity();

  rCf = Vector3d::Zero();
  rXf = Vector3d::Zero();
  cal_Fextf = Vector6d::Zero();

  rpreDes = new Vector3d[info->controlNodeNum];
  rpreDesabs = new Vector3d[info->controlNodeNum];
  qpreDes = new Quaternion4d[info->controlNodeNum];
  qpreDesabs = new Quaternion4d[info->controlNodeNum];
  fpreDes = new Vector3d[info->controlNodeNum];
  npreDes = new Vector3d[info->controlNodeNum];
  // amiyata
  rfinCur = new Vector3d[info->controlNodeNum];
  rfinCurabs = new Vector3d[info->controlNodeNum];
  qfinCur = new Quaternion4d[info->controlNodeNum];
  qfinCurabs = new Quaternion4d[info->controlNodeNum];
  ffinCur = new Vector3d[info->controlNodeNum];
  nfinCur = new Vector3d[info->controlNodeNum];

  rf = new Vector3d[info->controlNodeNum];
  rfabs = new Vector3d[info->controlNodeNum];
  xif = new Vector3d[info->controlNodeNum];
  xifabs = new Vector3d[info->controlNodeNum];
  qf = new Quaternion4d[info->controlNodeNum];
  qfabs = new Quaternion4d[info->controlNodeNum];
  ff = new Vector3d[info->controlNodeNum];
  nf = new Vector3d[info->controlNodeNum];

  // rtd = new Vector3d[info->controlNodeNum];
  rAp = new double[info->controlNodeNum];

  for(int i=0; i<info->controlNodeNum; i++){
    rpreDes[i] = Vector3d::Zero();
    rpreDesabs[i] = Vector3d::Zero();
    qpreDes[i] = Quaternion4d::Zero();
    qpreDesabs[i] = Quaternion4d::Zero();
    fpreDes[i] = Vector3d::Zero();
    npreDes[i] = Vector3d::Zero();
    // amiyata
    rfinCur[i] = Vector3d::Zero();
    rfinCurabs[i] = Vector3d::Zero();
    qfinCur[i] = Quaternion4d::Zero();
    qfinCurabs[i] = Quaternion4d::Zero();
    ffinCur[i] = Vector3d::Zero();
    nfinCur[i] = Vector3d::Zero();

    rf[i] = Vector3d::Zero();
    rfabs[i] = Vector3d::Zero();
    xif[i] = Vector3d::Zero();
    xifabs[i] = Vector3d::Zero();
    qf[i] = Quaternion4d::Identity();
    qfabs[i] = Quaternion4d::Identity();
    ff[i] = Vector3d::Zero();
    nf[i] = Vector3d::Zero();

    // rtd[i] = Vector3d::Zero(); // amiyata
    rAp[i] = 0.;
  }

  baseTranslationNum = 0;
  baseRotationNum = 0;

  controlNodeTranslationNum = new int[info->controlNodeNum];
  controlNodeRotationNum = new int[info->controlNodeNum];
  controlNodeForceNum = new int[info->controlNodeNum];
  controlNodeMomentNum = new int[info->controlNodeNum];

  controlNodeTranslationName = new string[info->controlNodeNum];
  controlNodeRotationName = new string[info->controlNodeNum];
  controlNodeForceName = new string[info->controlNodeNum];
  controlNodeMomentName = new string[info->controlNodeNum];

  //amiyata
  baseTranslationSpec = false;
  baseRotationSpec = false;
  comSpec = false;
  dcmSpec = false;
  externalWrenchSpec = false;

  controlNodeTranslationSpec = new bool[info->controlNodeNum];
  controlNodeRotationSpec = new bool[info->controlNodeNum];
  controlNodeForceSpec = new bool[info->controlNodeNum];
  controlNodeMomentSpec = new bool[info->controlNodeNum];

  for(int i=0; i<info->controlNodeNum; i++){
    controlNodeTranslationNum[i] = 0;
    controlNodeRotationNum[i] = 0;
    controlNodeForceNum[i] = 0;
    controlNodeMomentNum[i] = 0;

    controlNodeTranslationName[i] = "default";
    controlNodeRotationName[i] = "default";
    controlNodeForceName[i] = "default";
    controlNodeMomentName[i] = "default";

    controlNodeTranslationSpec[i] = false;
    controlNodeRotationSpec[i] = false;
    controlNodeForceSpec[i] = false;
    controlNodeMomentSpec[i] = false;
  }

  comNum = 0;
  dcmNum = 0;
  externalWrenchNum = 0;

  baseTranslationName
    = baseRotationName
    = comName
    = dcmName
    = externalWrenchName
    = "default";

  controlNodeTranslation_ptr =
    (void (RLS::DesiredValueGenerator::**)(const int&, const double&))malloc(sizeof(void (RLS::DesiredValueGenerator::*)(const int&, const double&))*info->controlNodeNum);
  controlNodeRotation_ptr =
    (void (RLS::DesiredValueGenerator::**)(const int&, const double&))malloc(sizeof(void (RLS::DesiredValueGenerator::*)(const int&, const double&))*info->controlNodeNum);
  controlNodeForce_ptr =
    (void (RLS::DesiredValueGenerator::**)(const int&, const double&))malloc(sizeof(void (RLS::DesiredValueGenerator::*)(const int&, const double&))*info->controlNodeNum);
  controlNodeMoment_ptr =
    (void (RLS::DesiredValueGenerator::**)(const int&, const double&))malloc(sizeof(void (RLS::DesiredValueGenerator::*)(const int&, const double&))*info->controlNodeNum);
}
