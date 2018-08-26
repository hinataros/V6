/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeControllerMap()
{
  if(debug) DEBUG;

  motionControllerName =
    momentumControllerName =
    forceControllerName =
    torqueControllerName =
    inverseDynamicsControllerName = "default";

  // mapping
  // motion controller
  map_momentumController["default"] = &RLS::RlsDynamics::zeroMomentum;
  map_momentumController["baseMomentum"] = &RLS::RlsDynamics::baseMomentum;
  map_momentumController["centroidalMomentum"] = &RLS::RlsDynamics::centroidalMomentum;
  map_momentumController["centroidalDcmMomentum"] = &RLS::RlsDynamics::centroidalDcmMomentum;
  map_momentumController["centroidalCmpMomentum"] = &RLS::RlsDynamics::centroidalCmpMomentum;

  map_motionController["default"] = &RLS::RlsDynamics::zeroMotion;
  map_motionController["baseVelocitySynergy"] = &RLS::RlsDynamics::baseVelocitySynergy;
  map_motionController["mixedVelocitySynergy"] = &RLS::RlsDynamics::mixedVelocitySynergy;

  map_motionController["workAcceleration"] = &RLS::RlsDynamics::workAcceleration;
  map_motionController["baseAccelerationSynergy"] = &RLS::RlsDynamics::baseAccelerationSynergy;
  map_motionController["mixedAccelerationSynergy"] = &RLS::RlsDynamics::mixedAccelerationSynergy;
  map_motionController["centroidalAccelerationSynergy"] = &RLS::RlsDynamics::centroidalAccelerationSynergy;
  map_motionController["raa"] = &RLS::RlsDynamics::raa;

  map_motionController["rest_cmlC"] = &RLS::RlsDynamics::rest_cmlC;
  map_motionController["rest_clCm"] = &RLS::RlsDynamics::rest_clCm;
  map_motionController["baseGeneralizedMomentum"] = &RLS::RlsDynamics::baseGeneralizedMomentum;
  map_motionController["mixedGeneralizedMomentum"] = &RLS::RlsDynamics::mixedGeneralizedMomentum;
  map_motionController["accelerationSolver"] = &RLS::RlsDynamics::accelerationSolver;
  map_motionController["hogehogeMomentum"] = &RLS::RlsDynamics::hogehogeMomentum;

  // force controller
  map_forceController["default"] = &RLS::RlsDynamics::zeroDistribution;
  map_forceController["baseDistribution"] = &RLS::RlsDynamics::baseDistribution;
  map_forceController["centroidalDistribution"] = &RLS::RlsDynamics::centroidalDistribution;
  map_forceController["centroidalDcmDistribution"] = &RLS::RlsDynamics::centroidalDcmDistribution;
  map_forceController["distributionSolver"] = &RLS::RlsDynamics::distributionSolver;

  // torque controller
  map_torqueController["default"] = &RLS::RlsDynamics::zeroTorque;
  map_torqueController["jointSpace"] = &RLS::RlsDynamics::jointSpace;
  map_torqueController["staticControl"] = &RLS::RlsDynamics::staticControl;
  map_torqueController["base"] = &RLS::RlsDynamics::base;
  map_torqueController["mixed"] = &RLS::RlsDynamics::mixed;
  map_torqueController["mixedmixed"] = &RLS::RlsDynamics::mixedmixed;
  map_torqueController["crb"] = &RLS::RlsDynamics::crb;
  map_torqueController["baseOpt"] = &RLS::RlsDynamics::baseOpt;
  map_torqueController["mixedOpt"] = &RLS::RlsDynamics::mixedOpt;
  map_torqueController["mixedmixedOpt"] = &RLS::RlsDynamics::mixedmixedOpt;

  // inverse dynamics controller
  map_inverseDynamicsController["default"] = &RLS::RlsDynamics::zeroDynamics;
  map_inverseDynamicsController["fullDynamics"] = &RLS::RlsDynamics::fullDynamicsController;
  map_inverseDynamicsController["momentumInverseDynamics"] = &RLS::RlsDynamics::momentumInverseDynamicsController;
  map_inverseDynamicsController["highGain"] = &RLS::RlsDynamics::highGainController;
  map_inverseDynamicsController["spatialDynamicsSolver"] = &RLS::RlsDynamics::spatialDynamicsSolver;
  map_inverseDynamicsController["dlrSolver"] = &RLS::RlsDynamics::dlrSolver;
}
