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
  eXt = des->rXDes - model->rXt; // amiyata
  // o(des->rXDes);
  // o(model->rX);
  // o(eX);

  drXfb = des->drXDes + KX*eX;
  drXtfb = des->drXDes + KX*eXt; // amiyata
}
