/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeFeedbackControllerMap()
{
  if(debug) DEBUG;

  baseTranslationFeedbackControllerName
    = baseOrientationFeedbackControllerName
    = controlNodeAccelerationFeedbackControllerName
    = controlNodeWrenchFeedbackControllerName
    = comFeedbackControllerName
    = dcmFeedbackControllerName
    = externalWrenchFeedbackControllerName
    = "default";

  // mapping
  // ********************************
  // base translation
  map_baseTranslationFeedbackController["default"]
    = &RLS::RlsDynamics::baseTranslationFBPI;

  // base orientation
  map_baseOrientationFeedbackController["default"]
    = &RLS::RlsDynamics::baseOrientationFBPI;

  // control node acceleration
  map_controlNodeAccelerationFeedbackController["default"]
    = &RLS::RlsDynamics::controlNodeAccelerationFBPI;

  // control node wrench
  map_controlNodeWrenchFeedbackController["default"]
    = &RLS::RlsDynamics::controlNodeWrenchFBFF;

  // com
  map_comFeedbackController["default"]
    = &RLS::RlsDynamics::comFBPI;
  map_comFeedbackController["dcmControl"]
    = &RLS::RlsDynamics::comFBDcmControl;

  // dcm
  map_dcmFeedbackController["default"]
    = &RLS::RlsDynamics::dcmFBPI;

  // external wrench
  map_externalWrenchFeedbackController["default"]
    = &RLS::RlsDynamics::externalWrenchFBFF;
}
