/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::feedbackController(const Model &model)
{
  if(debug) DEBUG;

  (this->*baseTranslationFeedbackController_ptr)(model.hoap2);
  (this->*baseOrientationFeedbackController_ptr)(model.hoap2);
  (this->*controlNodeAccelerationFeedbackController_ptr)(model.hoap2);
  (this->*controlNodeWrenchFeedbackController_ptr)(model.hoap2);
  (this->*comFeedbackController_ptr)(model.hoap2);
  (this->*dcmFeedbackController_ptr)(model.hoap2);
  (this->*externalWrenchFeedbackController_ptr)(model.hoap2);

  spatialFeedbackController(model);
}
