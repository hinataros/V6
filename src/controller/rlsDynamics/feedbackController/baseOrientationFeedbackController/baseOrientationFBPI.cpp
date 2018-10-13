/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::baseOrientationFBPI()
{
  if(debug) DEBUG;

  eoB = 0.5*(cross(model->RB.col(0))*des->RBDes.col(0)
             + cross(model->RB.col(1))*des->RBDes.col(1)
             + cross(model->RB.col(2))*des->RBDes.col(2));
  ewB = des->wBDes - model->wB;

  // velocityController
  wBfb = des->wBDes + KpwB*eoB;

  dwBfb = des->dwBDes + KdwB*ewB + KpwB*eoB;
}
