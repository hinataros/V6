/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::baseRotationCentroidalAngularDamping()
{
  if(debug) DEBUG;

  // only acceleration/torque controller
  dwBfb = - KDwC * model->wC;
}
