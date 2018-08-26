/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mapping()
{
  if(debug) DEBUG;

  baseTranslationTrajectory_ptr = map_baseTranslationTrajectory[baseTranslationTrajectoryName];
  baseOrientationTrajectory_ptr = map_baseOrientationTrajectory[baseOrientationTrajectoryName];
  endEffectorTrajectory_ptr = map_endEffectorTrajectory[endEffectorTrajectoryName];
  comTrajectory_ptr = map_comTrajectory[comTrajectoryName];
  dcmTrajectory_ptr = map_dcmTrajectory[dcmTrajectoryName];
  externalWrenchTrajectory_ptr = map_externalWrenchTrajectory[externalWrenchTrajectoryName];

  baseTranslationReference_ptr = map_baseTranslationReference[baseTranslationReferenceName];
  baseOrientationReference_ptr = map_baseOrientationReference[baseOrientationReferenceName];
  endEffectorReference_ptr = map_endEffectorReference[endEffectorReferenceName];
  comReference_ptr = map_comReference[comReferenceName];
  dcmReference_ptr = map_dcmReference[dcmReferenceName];
  externalWrenchReference_ptr = map_externalWrenchReference[externalWrenchReferenceName];

  motionController_ptr = map_motionController[motionControllerName];
  momentumController_ptr = map_momentumController[momentumControllerName];
  forceController_ptr = map_forceController[forceControllerName];
  torqueController_ptr = map_torqueController[torqueControllerName];
  inverseDynamicsController_ptr = map_inverseDynamicsController[inverseDynamicsControllerName];
}
