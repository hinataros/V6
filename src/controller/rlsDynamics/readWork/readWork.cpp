/**
   @author Sho Miyahara 2017
*/

#include <sys/stat.h>
#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::readWork(const TreeModel::Info &info, bool multi, string node, int num, int phase)
{
  struct stat statFile;
  if(stat(this->info.path_work.c_str(), &statFile)!=0){
    cout << manip_error("RlsDynamics::readWork() error...") << endl
         << manip_error("no such file '"+this->info.path_work+"'") << endl;

    return -1;
  }

  YAML::Node doc = YAML::LoadFile(this->info.path_work.c_str());

  if(node=="Sequence")
    readSequence(doc, multi, node, num, phase);

  desiredBaseTranslationGeneratorNum = updateValue<int>(doc, multi, node, num, phase, "Desired base translation generator", "num", desiredBaseTranslationGeneratorNum);
  desiredBaseTranslationGeneratorName = updateValue<string>(doc, multi, node, num, phase, "Desired base translation generator", "name", desiredBaseTranslationGeneratorName);
  desiredBaseOrientationGeneratorNum = updateValue<int>(doc, multi, node, num, phase, "Desired base orientation generator", "num", desiredBaseOrientationGeneratorNum);
  desiredBaseOrientationGeneratorName = updateValue<string>(doc, multi, node, num, phase, "Desired base orientation generator", "name", desiredBaseOrientationGeneratorName);

  desiredComGeneratorNum = updateValue<int>(doc, multi, node, num, phase, "Desired CoM generator", "num", desiredComGeneratorNum);
  desiredComGeneratorName = updateValue<string>(doc, multi, node, num, phase, "Desired CoM generator", "name", desiredComGeneratorName);
  desiredDcmGeneratorNum = updateValue<int>(doc, multi, node, num, phase, "Desired DCM generator", "num", desiredDcmGeneratorNum);
  desiredDcmGeneratorName = updateValue<string>(doc, multi, node, num, phase, "Desired DCM generator", "name", desiredDcmGeneratorName);
  desiredExternalWrenchGeneratorNum = updateValue<int>(doc, multi, node, num, phase, "Desired external wrench generator", "num", desiredExternalWrenchGeneratorNum);
  desiredExternalWrenchGeneratorName = updateValue<string>(doc, multi, node, num, phase, "Desired external wrench generator", "name", desiredExternalWrenchGeneratorName);

  baseTranslationFeedbackControllerName = updateValue<string>(doc, multi, node, num, phase, "Base translation feedback controller", baseTranslationFeedbackControllerName);
  baseOrientationFeedbackControllerName = updateValue<string>(doc, multi, node, num, phase, "Base orientation feedback controller", baseOrientationFeedbackControllerName);
  controlNodeAccelerationFeedbackControllerName = updateValue<string>(doc, multi, node, num, phase, "Control node acceleration feedback controller", controlNodeAccelerationFeedbackControllerName);
  controlNodeWrenchFeedbackControllerName = updateValue<string>(doc, multi, node, num, phase, "Control node wrench feedback controller", controlNodeWrenchFeedbackControllerName);
  comFeedbackControllerName = updateValue<string>(doc, multi, node, num, phase, "CoM feedback controller", comFeedbackControllerName);
  dcmFeedbackControllerName = updateValue<string>(doc, multi, node, num, phase, "DCM feedback controller", dcmFeedbackControllerName);
  externalWrenchFeedbackControllerName = updateValue<string>(doc, multi, node, num, phase, "External wrench feedback controller", externalWrenchFeedbackControllerName);

  inverseDynamicsControllerName = updateValue<string>(doc, multi, node, num, phase, "Inverse dynamics controller", inverseDynamicsControllerName);
  motionControllerName = updateValue<string>(doc, multi, node, num, phase, "Motion controller", motionControllerName);
  momentumControllerName = updateValue<string>(doc, multi, node, num, phase, "Momentum controller", momentumControllerName);
  internalForceControllerName = updateValue<string>(doc, multi, node, num, phase, "Internal force controller", internalForceControllerName);
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

