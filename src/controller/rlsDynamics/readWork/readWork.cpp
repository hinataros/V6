/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::readWork(const string work_path, bool multi, string node, int num, int phase, int controlNodeNum)
{
  YAML::Node doc = YAML::LoadFile(work_path.c_str());

  if(node=="Sequence")
    readSequence(doc, multi, node, num, phase, controlNodeNum);

  baseTranslationTrajectoryNum = updateValue<int>(doc, multi, node, num, phase, "Base translation trajectory", "num", baseTranslationTrajectoryNum);
  baseTranslationTrajectoryName = updateValue<string>(doc, multi, node, num, phase, "Base translation trajectory", "name", baseTranslationTrajectoryName);
  baseOrientationTrajectoryNum = updateValue<int>(doc, multi, node, num, phase, "Base orientation trajectory", "num", baseOrientationTrajectoryNum);
  baseOrientationTrajectoryName = updateValue<string>(doc, multi, node, num, phase, "Base orientation trajectory", "name", baseOrientationTrajectoryName);
  endEffectorTrajectoryNum = updateValue<int>(doc, multi, node, num, phase, "End effector trajectory", "num", endEffectorTrajectoryNum);
  endEffectorTrajectoryName = updateValue<string>(doc, multi, node, num, phase, "End effector trajectory", "name", endEffectorTrajectoryName);
  comTrajectoryNum = updateValue<int>(doc, multi, node, num, phase, "CoM trajectory", "num", comTrajectoryNum);
  comTrajectoryName = updateValue<string>(doc, multi, node, num, phase, "CoM trajectory", "name", comTrajectoryName);
  dcmTrajectoryNum = updateValue<int>(doc, multi, node, num, phase, "DCM trajectory", "num", dcmTrajectoryNum);
  dcmTrajectoryName = updateValue<string>(doc, multi, node, num, phase, "DCM trajectory", "name", dcmTrajectoryName);
  externalWrenchTrajectoryNum = updateValue<int>(doc, multi, node, num, phase, "External wrench trajectory", "num", externalWrenchTrajectoryNum);
  externalWrenchTrajectoryName = updateValue<string>(doc, multi, node, num, phase, "External wrench trajectory", "name", externalWrenchTrajectoryName);

  baseTranslationReferenceName = updateValue<string>(doc, multi, node, num, phase, "Base translation reference", baseTranslationReferenceName);
  baseOrientationReferenceName = updateValue<string>(doc, multi, node, num, phase, "Base orientation reference", baseOrientationReferenceName);
  endEffectorReferenceName = updateValue<string>(doc, multi, node, num, phase, "End effector reference", endEffectorReferenceName);
  comReferenceName = updateValue<string>(doc, multi, node, num, phase, "CoM reference", comReferenceName);
  dcmReferenceName = updateValue<string>(doc, multi, node, num, phase, "DCM reference", dcmReferenceName);
  externalWrenchReferenceName = updateValue<string>(doc, multi, node, num, phase, "External wrench reference", externalWrenchReferenceName);

  inverseDynamicsControllerName = updateValue<string>(doc, multi, node, num, phase, "Inverse dynamics controller", inverseDynamicsControllerName);
  motionControllerName = updateValue<string>(doc, multi, node, num, phase, "Motion controller", motionControllerName);
  momentumControllerName = updateValue<string>(doc, multi, node, num, phase, "Momentum controller", momentumControllerName);
  forceControllerName = updateValue<string>(doc, multi, node, num, phase, "Force controller", forceControllerName);
  torqueControllerName = updateValue<string>(doc, multi, node, num, phase, "Torque controller", torqueControllerName);

  Bc_kDiag = updateDiagonalMatrix<MatrixXi>(doc, multi, node, num, phase, "Bc", controlNodeNum, Bc_kDiag);
  Bm_kDiag = updateDiagonalMatrix<MatrixXi>(doc, multi, node, num, phase, "Bm", controlNodeNum, Bm_kDiag);

  BpDiag = updateDiagonalMatrix<MatrixXi>(doc, multi, node, num, phase, "Bp", controlNodeNum, BpDiag);

  KpC = updateDiagonalMatrix<Matrix3d>(doc, multi, node, num, phase, "KpC", KpC);
  KdC = updateDiagonalMatrix<Matrix3d>(doc, multi, node, num, phase, "KdC", KdC);

  KpvB = updateDiagonalMatrix<Matrix3d>(doc, multi, node, num, phase, "KpvB", KpvB);
  KdvB = updateDiagonalMatrix<Matrix3d>(doc, multi, node, num, phase, "KdvB", KdvB);

  KpwB = updateDiagonalMatrix<Matrix3d>(doc, multi, node, num, phase, "KpwB", KpwB);
  KdwB = updateDiagonalMatrix<Matrix3d>(doc, multi, node, num, phase, "KdwB", KdwB);

  KX = updateDiagonalMatrix<Matrix3d>(doc, multi, node, num, phase, "KX", KX);

  Kpv = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "Kpv", controlNodeNum, Kpv);
  Kdv = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "Kdv", controlNodeNum, Kdv);

  Kpp = updateDiagonalMatrix<Matrix2d>(doc, multi, node, num, phase, "Kpp", Kpp);

  KDlC = updateDiagonalMatrix<Matrix3d>(doc, multi, node, num, phase, "KDlC", KDlC);
  KDth = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "KDth", controlNodeNum, KDth);

  Kthinit = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "Kthinit", controlNodeNum, Kthinit);

  // high gain control
  KpHG = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "KpHG", controlNodeNum, KpHG);
  KdHG = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "KdHG", controlNodeNum, KdHG);

  // optimization weight
  Wdh = updateDiagonalMatrix<Matrix6d>(doc, multi, node, num, phase, "Wdh", Wdh);
  Wp = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "Wp", controlNodeNum, Wp);
  WF = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "WF", controlNodeNum, WF);
  WFmin = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "WFmin", controlNodeNum, WFmin);
  Wm = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "Wm", controlNodeNum, Wm);
  WJ = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "WJ", controlNodeNum, WJ);
  Wth = updateDiagonalMatrix<MatrixXd>(doc, multi, node, num, phase, "Wth", controlNodeNum, Wth);

  // others
  cal_Xtd = updateVector<VectorXd>(doc, multi, node, num, phase, "cal_Xtd", controlNodeNum, cal_Xtd);

  // // transform offset
  // if(multiSequence){
  //   if(!checkNode(doc, node, num, phase, name))
  //     for(int i=0; i<controlNodeNum; i++)
  //       rkk[i] = readVector<VectorXd>(doc, node, seq, "rkk", i, 3);

  return 1;
}

