/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::controlNodeForceFF()
{
  if(debug) DEBUG;

  cal_Ffb = des->cal_FDes;
}
