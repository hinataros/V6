/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::readWork(string work_path, const TreeModel::Info &info, bool multi, string node, int num, int phase)
{
  YAML::Node doc = YAML::LoadFile(work_path.c_str());

  if(node=="Sequence")
    readSequence(doc, multi, node, num, phase, info.controlNodeNum);

  baseTranslationTrajectoryNum = updateValue<int>(doc, multi, node, num, phase, "Base translation trajectory", "num", baseTranslationTrajectoryNum);
  baseTranslationTrajectoryName = updateValue<string>(doc, multi, node, num, phase, "Base translation trajectory", "name", baseTranslationTrajectoryName);
  baseOrientationTrajectoryNum = updateValue<int>(doc, multi, node, num, phase, "Base orientation trajectory", "num", baseOrientationTrajectoryNum);
  baseOrientationTrajectoryName = updateValue<string>(doc, multi, node, num, phase, "Base orientation trajectory", "name", baseOrientationTrajectoryName);

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

  KpC = updateValue<Matrix3d>(doc, multi, node, num, phase, "KpC", KpC);
  KdC = updateValue<Matrix3d>(doc, multi, node, num, phase, "KdC", KdC);

  KpvB = updateValue<Matrix3d>(doc, multi, node, num, phase, "KpvB", KpvB);
  KdvB = updateValue<Matrix3d>(doc, multi, node, num, phase, "KdvB", KdvB);

  KpwB = updateValue<Matrix3d>(doc, multi, node, num, phase, "KpwB", KpwB);
  KdwB = updateValue<Matrix3d>(doc, multi, node, num, phase, "KdwB", KdwB);

  KX = updateValue<Matrix3d>(doc, multi, node, num, phase, "KX", KX);

  Kpp = updateValue<Matrix2d>(doc, multi, node, num, phase, "Kpp", Kpp);

  KDlC = updateValue<Matrix3d>(doc, multi, node, num, phase, "KDlC", KDlC);

  // optimization weight
  Wdh = updateValue<Matrix6d>(doc, multi, node, num, phase, "Wdh", Wdh);

  readControlNode(doc, info, multi, node, num, phase);

  // // transform offset
  // if(multiSequence){
  //   if(!checkNode(doc, node, num, phase, name))
  //     for(int i=0; i<controlNodeNum; i++)
  //       rkk[i] = readVector<VectorXd>(doc, node, seq, "rkk", i, 3);

  return 1;
}

