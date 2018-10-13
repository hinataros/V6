/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::readController()
{
  if(debug) DEBUG;

  yamlInfo->checkValue<string>(baseTranslationFeedbackControllerName,
                               "Base translation feedback controller");
  yamlInfo->checkValue<string>(baseOrientationFeedbackControllerName,
                               "Base orientation feedback controller");
  yamlInfo->checkValue<string>(controlNodeAccelerationFeedbackControllerName,
                               "Control node acceleration feedback controller");
  yamlInfo->checkValue<string>(controlNodeWrenchFeedbackControllerName,
                               "Control node wrench feedback controller");
  yamlInfo->checkValue<string>(comFeedbackControllerName,
                               "CoM feedback controller");
  yamlInfo->checkValue<string>(dcmFeedbackControllerName,
                               "DCM feedback controller");
  yamlInfo->checkValue<string>(externalWrenchFeedbackControllerName,
                               "External wrench feedback controller");

  yamlInfo->checkValue<Matrix3d>(KpC, "KpC");
  yamlInfo->checkValue<Matrix3d>(KdC, "KdC");

  yamlInfo->checkValue<Matrix3d>(KpvB, "KpvB");
  yamlInfo->checkValue<Matrix3d>(KdvB, "KdvB");

  yamlInfo->checkValue<Matrix3d>(KpwB, "KpwB");
  yamlInfo->checkValue<Matrix3d>(KdwB, "KdwB");

  yamlInfo->checkValue<Matrix3d>(KX, "KX");

  for(int i=0; i<info->controlNodeNum; i++){
    string name = info->controlNode[i].name;

    Matrix6d temp = Kpv.block(6*i,6*i,6,6);
    yamlInfo->checkValue<Matrix6d>(temp, "Kpv", name);
    Kpv.block(6*i,6*i,6,6) = temp;

    temp = Kdv.block(6*i,6*i,6,6);
    yamlInfo->checkValue<Matrix6d>(temp, "Kdv", name);
    Kdv.block(6*i,6*i,6,6) = temp;
  }
}
