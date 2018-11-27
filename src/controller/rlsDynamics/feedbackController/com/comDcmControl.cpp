/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::comDcmControl()
{
  if(debug) DEBUG;

  dvCfb = model->wX*(drXfb - model->vC);
}