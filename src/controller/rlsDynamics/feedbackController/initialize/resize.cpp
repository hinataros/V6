/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::resize()
{
  if(debug) DEBUG;

  KpC = Matrix3d::Zero();
  KdC = Matrix3d::Zero();

  KpvB = Matrix3d::Zero();
  KdvB = Matrix3d::Zero();

  KpwB = Matrix3d::Zero();
  KdwB = Matrix3d::Zero();

  KX = Matrix3d::Zero();

  Kpv = MatrixXd::Zero(6*info->controlNodeNum, 6*info->controlNodeNum);
  Kdv = MatrixXd::Zero(6*info->controlNodeNum, 6*info->controlNodeNum);

  erC = evC = Vector3d::Zero();
  erB = evB = eoB = ewB = Vector3d::Zero();
  cal_Ep = cal_Ev = VectorXd::Zero(6*info->controlNodeNum);

  vBfb = Vector3d::Zero();
  dvBfb = Vector3d::Zero();

  wBfb = Vector3d::Zero();
  dwBfb = Vector3d::Zero();

  cal_VBfb = Vector6d::Zero();
  cal_dVBfb = Vector6d::Zero();

  cal_Vfb = VectorXd::Zero(6*info->controlNodeNum);
  cal_dVfb = VectorXd::Zero(6*info->controlNodeNum);

  vCfb = Vector3d::Zero();
  dvCfb = Vector3d::Zero();

  cal_VMfb = Vector6d::Zero();
  cal_dVMfb = Vector6d::Zero();

  cal_dVCfb = Vector6d::Zero();

  drXfb = Vector3d::Zero();

  cal_Ffb = VectorXd::Zero(6*info->controlNodeNum);

  baseTranslationFeedbackControllerName
    = baseOrientationFeedbackControllerName
    = controlNodeAccelerationFeedbackControllerName
    = controlNodeWrenchFeedbackControllerName
    = comFeedbackControllerName
    = dcmFeedbackControllerName
    = externalWrenchFeedbackControllerName
    = "default";
}
