/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::setMap()
{
  if(debug) DEBUG;

  // base translation
  baseTranslation_map["default"]
    = &RLS::FeedbackController::baseTranslationPI;

  // base orientation
  baseRotation_map["default"]
    = &RLS::FeedbackController::baseRotationPI;
  baseRotation_map["wCDamp"] = &RLS::FeedbackController::baseRotationCentroidalAngularDamping;

  // control node motion
  controlNodeMotion_map["default"]
    = &RLS::FeedbackController::controlNodeMotionPI;

  // control node force
  controlNodeForce_map["default"]
    = &RLS::FeedbackController::controlNodeForceFF;

  // com
  com_map["default"]
    = &RLS::FeedbackController::comPI;
  com_map["dcmControl"]
    = &RLS::FeedbackController::comDcmControl;

  // dcm
  dcm_map["default"]
    = &RLS::FeedbackController::dcmPI;

  // external wrench
  externalWrench_map["default"]
    = &RLS::FeedbackController::externalWrenchFF;
}
