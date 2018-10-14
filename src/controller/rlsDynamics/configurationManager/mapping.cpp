/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mapping()
{
  if(debug) DEBUG;

  if(extMotionController)
    ext_motionController_ptr = ext_motionController_map[motionControllerName];
  if(extMomentumController)
    ext_momentumController_ptr = ext_momentumController_map[momentumControllerName];
  if(extForceController)
    ext_forceController_ptr = ext_forceController_map[forceControllerName];
  if(extTorqueController)
    ext_torqueController_ptr = ext_torqueController_map[torqueControllerName];
  if(extInverseDynamicsController)
    ext_inverseDynamicsController_ptr = ext_inverseDynamicsController_map[inverseDynamicsControllerName];
  if(extExternalWrenchController)
    ext_externalWrenchController_ptr = ext_externalWrenchController_map[externalWrenchControllerName];

  motionController_ptr = motionController_map[motionControllerName];
  operationalSpaceController_ptr = operationalSpaceController_map[operationalSpaceControllerName];
  momentumController_ptr = momentumController_map[momentumControllerName];
  internalForceController_ptr = internalForceController_map[internalForceControllerName];
  forceController_ptr = forceController_map[forceControllerName];
  torqueController_ptr = torqueController_map[torqueControllerName];
  inverseDynamicsController_ptr = inverseDynamicsController_map[inverseDynamicsControllerName];

  externalWrenchController_ptr = externalWrenchController_map[externalWrenchControllerName];
}
