/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::baseRotationPI()
{
  if(debug) DEBUG;

  Quaternion4d qe = Quaternion4d::R2q(model->RB);
  eoB = qe.w*des->qBDes.v - des->qBDes.w*qe.v - cross(des->qBDes.v)*qe.v;
  // eoB = orientationError(des->RBDes, model->RB);
  ewB = des->wBDes - model->wB;

  // velocityController
  wBfb = des->wBDes + KpwB*eoB;

  dwBfb = des->dwBDes + KdwB*ewB + KpwB*eoB;
}
