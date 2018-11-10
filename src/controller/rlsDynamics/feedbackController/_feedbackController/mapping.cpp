/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::mapping()
{
  if(debug) DEBUG;

  baseTranslation_ptr = baseTranslation_map[baseTranslationName];
  baseRotation_ptr = baseRotation_map[baseRotationName];
  controlNodeMotion_ptr = controlNodeMotion_map[controlNodeMotionName];
  controlNodeForce_ptr = controlNodeForce_map[controlNodeForceName];
  com_ptr = com_map[comName];
  dcm_ptr = dcm_map[dcmName];
  externalWrench_ptr = externalWrench_map[externalWrenchName];
}
