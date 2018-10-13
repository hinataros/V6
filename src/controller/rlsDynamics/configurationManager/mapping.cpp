/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mapping()
{
  if(debug) DEBUG;

  motionController_ptr = map_motionController[motionControllerName];
  operationalSpaceController_ptr = map_operationalSpaceController[operationalSpaceControllerName];
  momentumController_ptr = map_momentumController[momentumControllerName];
  internalForceController_ptr = map_internalForceController[internalForceControllerName];
  forceController_ptr = map_forceController[forceControllerName];
  torqueController_ptr = map_torqueController[torqueControllerName];
  inverseDynamicsController_ptr = map_inverseDynamicsController[inverseDynamicsControllerName];

  externalWrenchController_ptr = map_externalWrenchController[externalWrenchControllerName];
}
