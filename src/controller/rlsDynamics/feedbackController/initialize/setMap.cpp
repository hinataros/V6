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
  baseTranslationFeedbackController_map["default"]
    = &RLS::FeedbackController::baseTranslationFBPI;

  // base orientation
  baseOrientationFeedbackController_map["default"]
    = &RLS::FeedbackController::baseOrientationFBPI;

  // control node motion
  controlNodeMotionFeedbackController_map["default"]
    = &RLS::FeedbackController::controlNodeMotionFBPI;

  // control node force
  controlNodeForceFeedbackController_map["default"]
    = &RLS::FeedbackController::controlNodeForceFBFF;

  // com
  comFeedbackController_map["default"]
    = &RLS::FeedbackController::comFBPI;
  comFeedbackController_map["dcmControl"]
    = &RLS::FeedbackController::comFBDcmControl;

  // dcm
  dcmFeedbackController_map["default"]
    = &RLS::FeedbackController::dcmFBPI;

  // external wrench
  externalWrenchFeedbackController_map["default"]
    = &RLS::FeedbackController::externalWrenchFBFF;
}
