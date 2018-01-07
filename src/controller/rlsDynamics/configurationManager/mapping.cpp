/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mapping(Config &config)
{
  if(config.flag.debug) DEBUG;

  motionController_ptr = map_motionController[motionControllerName];
  momentumController_ptr = map_momentumController[momentumControllerName];
  forceController_ptr = map_forceController[forceControllerName];
  torqueController_ptr = map_torqueController[torqueControllerName];
  inverseDynamicsController_ptr = map_inverseDynamicsController[inverseDynamicsControllerName];
}
