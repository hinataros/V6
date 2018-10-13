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
  map_baseTranslationFeedbackController["default"]
    = &RLS::FeedbackController::baseTranslationFBPI;

  // base orientation
  map_baseOrientationFeedbackController["default"]
    = &RLS::FeedbackController::baseOrientationFBPI;

  // control node acceleration
  map_controlNodeAccelerationFeedbackController["default"]
    = &RLS::FeedbackController::controlNodeAccelerationFBPI;

  // control node wrench
  map_controlNodeWrenchFeedbackController["default"]
    = &RLS::FeedbackController::controlNodeWrenchFBFF;

  // com
  map_comFeedbackController["default"]
    = &RLS::FeedbackController::comFBPI;
  map_comFeedbackController["dcmControl"]
    = &RLS::FeedbackController::comFBDcmControl;

  // dcm
  map_dcmFeedbackController["default"]
    = &RLS::FeedbackController::dcmFBPI;

  // external wrench
  map_externalWrenchFeedbackController["default"]
    = &RLS::FeedbackController::externalWrenchFBFF;
}
