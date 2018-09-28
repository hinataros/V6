/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mapping(const int &controlNodeNum)
{
  if(debug) DEBUG;

  desiredBaseTranslationGenerator_ptr = map_desiredBaseTranslationGenerator[desiredBaseTranslationGeneratorName];
  desiredBaseOrientationGenerator_ptr = map_desiredBaseOrientationGenerator[desiredBaseOrientationGeneratorName];

  for(int i=0; i<controlNodeNum; i++){
    desiredControlNodeAccelerationGenerator_ptr[i] = map_desiredControlNodeAccelerationGenerator[i][desiredControlNodeAccelerationGeneratorName[i]];
    desiredControlNodeWrenchGenerator_ptr[i] = map_desiredControlNodeWrenchGenerator[i][desiredControlNodeWrenchGeneratorName[i]];
  }

  desiredComGenerator_ptr = map_desiredComGenerator[desiredComGeneratorName];
  desiredDcmGenerator_ptr = map_desiredDcmGenerator[desiredDcmGeneratorName];
  desiredExternalWrenchGenerator_ptr = map_desiredExternalWrenchGenerator[desiredExternalWrenchGeneratorName];

  baseTranslationFeedbackController_ptr = map_baseTranslationFeedbackController[baseTranslationFeedbackControllerName];
  baseOrientationFeedbackController_ptr = map_baseOrientationFeedbackController[baseOrientationFeedbackControllerName];
  controlNodeAccelerationFeedbackController_ptr = map_controlNodeAccelerationFeedbackController[controlNodeAccelerationFeedbackControllerName];
  controlNodeWrenchFeedbackController_ptr = map_controlNodeWrenchFeedbackController[controlNodeWrenchFeedbackControllerName];
  comFeedbackController_ptr = map_comFeedbackController[comFeedbackControllerName];
  dcmFeedbackController_ptr = map_dcmFeedbackController[dcmFeedbackControllerName];
  externalWrenchFeedbackController_ptr = map_externalWrenchFeedbackController[externalWrenchFeedbackControllerName];

  motionController_ptr = map_motionController[motionControllerName];
  momentumController_ptr = map_momentumController[momentumControllerName];
  internalForceController_ptr = map_internalForceController[internalForceControllerName];
  forceController_ptr = map_forceController[forceControllerName];
  torqueController_ptr = map_torqueController[torqueControllerName];
  inverseDynamicsController_ptr = map_inverseDynamicsController[inverseDynamicsControllerName];
}
