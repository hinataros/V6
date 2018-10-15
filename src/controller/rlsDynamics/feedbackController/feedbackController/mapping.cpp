/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::mapping()
{
  if(debug) DEBUG;

  baseTranslationFeedbackController_ptr = baseTranslationFeedbackController_map[baseTranslationFeedbackControllerName];
  baseOrientationFeedbackController_ptr = baseOrientationFeedbackController_map[baseOrientationFeedbackControllerName];
  controlNodeMotionFeedbackController_ptr = controlNodeMotionFeedbackController_map[controlNodeMotionFeedbackControllerName];
  controlNodeForceFeedbackController_ptr = controlNodeForceFeedbackController_map[controlNodeForceFeedbackControllerName];
  comFeedbackController_ptr = comFeedbackController_map[comFeedbackControllerName];
  dcmFeedbackController_ptr = dcmFeedbackController_map[dcmFeedbackControllerName];
  externalWrenchFeedbackController_ptr = externalWrenchFeedbackController_map[externalWrenchFeedbackControllerName];
}
