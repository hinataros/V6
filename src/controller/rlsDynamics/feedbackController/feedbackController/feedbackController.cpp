/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::feedbackController()
{
  if(debug) DEBUG;

  (this->*baseTranslationFeedbackController_ptr)();
  (this->*baseOrientationFeedbackController_ptr)();
  (this->*controlNodeAccelerationFeedbackController_ptr)();
  (this->*controlNodeWrenchFeedbackController_ptr)();
  (this->*comFeedbackController_ptr)();
  (this->*dcmFeedbackController_ptr)();
  (this->*externalWrenchFeedbackController_ptr)();

  stack();
}
