/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::mapping()
{
  if(debug) DEBUG;

  baseTranslationFeedbackController_ptr = map_baseTranslationFeedbackController[baseTranslationFeedbackControllerName];
  baseOrientationFeedbackController_ptr = map_baseOrientationFeedbackController[baseOrientationFeedbackControllerName];
  controlNodeAccelerationFeedbackController_ptr = map_controlNodeAccelerationFeedbackController[controlNodeAccelerationFeedbackControllerName];
  controlNodeWrenchFeedbackController_ptr = map_controlNodeWrenchFeedbackController[controlNodeWrenchFeedbackControllerName];
  comFeedbackController_ptr = map_comFeedbackController[comFeedbackControllerName];
  dcmFeedbackController_ptr = map_dcmFeedbackController[dcmFeedbackControllerName];
  externalWrenchFeedbackController_ptr = map_externalWrenchFeedbackController[externalWrenchFeedbackControllerName];
}
