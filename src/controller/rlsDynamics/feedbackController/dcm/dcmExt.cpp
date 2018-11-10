 /**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::dcmExt()
{
  if(debug) DEBUG;

  eX = des->rXBarDes - model->rX;

  drXfb = des->drXBarDes + KX*eX;
}
