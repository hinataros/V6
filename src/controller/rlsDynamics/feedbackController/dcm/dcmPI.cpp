 /**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::dcmPI()
{
  if(debug) DEBUG;

  eX = des->rXDes - model->rX;

  drXfb = des->drXDes + KX*eX;
}
