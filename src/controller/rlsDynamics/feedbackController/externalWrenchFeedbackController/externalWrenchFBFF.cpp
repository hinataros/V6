/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::externalWrenchFBFF()
{
  if(debug) DEBUG;

  cal_Fextfb = des->cal_FextDes;
}
