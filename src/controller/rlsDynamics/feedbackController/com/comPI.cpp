/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::comPI()
{
  if(debug) DEBUG;

  erC = des->rCDes - model->rC;
  evC = des->vCDes - model->vC;

  // velocityController
  vCfb = des->vCDes + KpC*erC;

  dvCfb = des->dvCDes + KdC*evC + KpC*erC;
}
