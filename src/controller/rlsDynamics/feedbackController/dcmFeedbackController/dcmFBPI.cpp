 /**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::dcmFBPI()
{
  if(debug) DEBUG;

  eX = des->rXDes - model->rX;

  drXfb = des->drXDes + KX*eX;
}
