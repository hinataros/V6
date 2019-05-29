/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::readController()
{
  if(debug) DEBUG;

  string feedbackControllerKeyName = "feedback controller";

  yamlInfo->checkValue<string>(baseTranslationName, feedbackControllerKeyName,
                               "base translation");
  yamlInfo->checkValue<string>(baseRotationName, feedbackControllerKeyName,
                               "base rotation");
  yamlInfo->checkValue<string>(controlNodeMotionName, feedbackControllerKeyName,
                               "control node motion");
  yamlInfo->checkValue<string>(controlNodeForceName, feedbackControllerKeyName,
                               "control node force");
  yamlInfo->checkValue<string>(comName, feedbackControllerKeyName,
                               "CoM");
  yamlInfo->checkValue<string>(dcmName, feedbackControllerKeyName,
                               "DCM");
  yamlInfo->checkValue<string>(externalWrenchName, feedbackControllerKeyName,
                               "external wrench");

  yamlInfo->checkValue<Matrix3d>(KpC, "KpC");
  yamlInfo->checkValue<Matrix3d>(KdC, "KdC");

  yamlInfo->checkValue<Matrix3d>(KpvB, "KpvB");
  yamlInfo->checkValue<Matrix3d>(KdvB, "KdvB");

  yamlInfo->checkValue<Matrix3d>(KpwB, "KpwB");
  yamlInfo->checkValue<Matrix3d>(KdwB, "KdwB");

  yamlInfo->checkValue<Matrix3d>(KX, "KX");

  yamlInfo->checkValue<Matrix3d>(KDwC, "KDwC"); // amiyata

  for(int i=0; i<info->controlNodeNum; i++){
    string name = info->controlNode[i].name;

    Matrix3d temp = Kpv.block(6*i,6*i,3,3);
    yamlInfo->checkValue<Matrix3d>(temp, "Kpv", name);
    Kpv.block(6*i,6*i,3,3) = temp;

    temp = Kpv.block(6*i+3,6*i+3,3,3);
    yamlInfo->checkValue<Matrix3d>(temp, "Kpw", name);
    Kpv.block(6*i+3,6*i+3,3,3) = temp;

    temp = Kdv.block(6*i,6*i,3,3);
    yamlInfo->checkValue<Matrix3d>(temp, "Kdv", name);
    Kdv.block(6*i,6*i,3,3) = temp;

    temp = Kdv.block(6*i+3,6*i+3,3,3);
    yamlInfo->checkValue<Matrix3d>(temp, "Kdw", name);
    Kdv.block(6*i+3,6*i+3,3,3) = temp;
  }
}
