/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mapping(const int &controlNodeNum)
{
  if(debug) DEBUG;

  baseTranslationTrajectory_ptr = map_baseTranslationTrajectory[baseTranslationTrajectoryName];
  baseOrientationTrajectory_ptr = map_baseOrientationTrajectory[baseOrientationTrajectoryName];

  for(int i=0; i<controlNodeNum; i++)
    controlNodeTrajectory_ptr[i] = map_controlNodeTrajectory[i][controlNodeTrajectoryName[i]];

  comTrajectory_ptr = map_comTrajectory[comTrajectoryName];
  dcmTrajectory_ptr = map_dcmTrajectory[dcmTrajectoryName];
  externalWrenchTrajectory_ptr = map_externalWrenchTrajectory[externalWrenchTrajectoryName];

  baseTranslationReference_ptr = map_baseTranslationReference[baseTranslationReferenceName];
  baseOrientationReference_ptr = map_baseOrientationReference[baseOrientationReferenceName];
  controlNodeReference_ptr = map_controlNodeReference[controlNodeReferenceName];
  comReference_ptr = map_comReference[comReferenceName];
  dcmReference_ptr = map_dcmReference[dcmReferenceName];
  externalWrenchReference_ptr = map_externalWrenchReference[externalWrenchReferenceName];

  motionController_ptr = map_motionController[motionControllerName];
  momentumController_ptr = map_momentumController[momentumControllerName];
  forceController_ptr = map_forceController[forceControllerName];
  torqueController_ptr = map_torqueController[torqueControllerName];
  inverseDynamicsController_ptr = map_inverseDynamicsController[inverseDynamicsControllerName];
}
