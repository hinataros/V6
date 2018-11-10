/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::baseTranslationPI()
{
  if(debug) DEBUG;

  erB = des->rBDes - model->rB;
  evB = des->vBDes - model->vB;

  // velocityController
  vBfb = des->vBDes + KpvB*erB;

  dvBfb = des->dvBDes + KdvB*evB + KpvB*erB;
}
