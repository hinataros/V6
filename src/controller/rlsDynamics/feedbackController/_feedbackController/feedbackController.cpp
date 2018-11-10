/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::feedbackController()
{
  if(debug) DEBUG;

  (this->*baseTranslation_ptr)();
  (this->*baseRotation_ptr)();
  (this->*controlNodeMotion_ptr)();
  (this->*controlNodeForce_ptr)();
  (this->*com_ptr)();
  (this->*dcm_ptr)();
  (this->*externalWrench_ptr)();

  stack();
}
