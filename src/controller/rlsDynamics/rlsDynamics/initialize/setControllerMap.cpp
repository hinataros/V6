/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::setControllerMap()
{
  if(debug) DEBUG;

  // momentum controller
  // ****************************************************************
  map_momentumController["default"] = &RLS::RlsDynamics::defaultController;
  map_momentumController["baseMomentum"] = &RLS::RlsDynamics::baseMomentum;
  map_momentumController["centroidalMomentum"] = &RLS::RlsDynamics::centroidalMomentum;
  map_momentumController["centroidalDcmMomentum"] = &RLS::RlsDynamics::centroidalDcmMomentum;
  map_momentumController["centroidalCmpMomentum"] = &RLS::RlsDynamics::centroidalCmpMomentum;

  // motion controller
  map_motionController["default"] = &RLS::RlsDynamics::defaultConfigurationController;

  // operational space reference
  // ****************************************************************
  // velocity controller
  map_operationalSpaceController["default"] = &RLS::RlsDynamics::defaultController;
  map_operationalSpaceController["relativeVelocityBaseMap"] = &RLS::RlsDynamics::relativeVelocityBaseMap;
  map_operationalSpaceController["relativeVelocityMixedMap"] = &RLS::RlsDynamics::relativeVelocityMixedMap;

  // acceleration controller
  map_operationalSpaceController["decomposeEndEffectorAcceleration"] = &RLS::RlsDynamics::decomposeEndEffectorAcceleration;
  map_operationalSpaceController["relativeAccelerationBaseMap"] = &RLS::RlsDynamics::relativeAccelerationBaseMap;
  map_operationalSpaceController["relativeAccelerationMixedMap"] = &RLS::RlsDynamics::relativeAccelerationMixedMap;
  map_operationalSpaceController["relativeAccelerationCentroidalMap"] = &RLS::RlsDynamics::relativeAccelerationCentroidalMap;

  // configuration space controller
  // ****************************************************************
  // velocity controller
  map_motionController["baseVelocitySynergy"] = &RLS::RlsDynamics::baseVelocitySynergy;
  map_motionController["mixedVelocitySynergy"] = &RLS::RlsDynamics::mixedVelocitySynergy;

  // acceleration controller
  map_motionController["workAcceleration"] = &RLS::RlsDynamics::workAcceleration;
  map_motionController["baseAccelerationSynergy"] = &RLS::RlsDynamics::baseAccelerationSynergy;
  map_motionController["mixedAccelerationSynergy"] = &RLS::RlsDynamics::mixedAccelerationSynergy;
  map_motionController["centroidalAccelerationSynergy"] = &RLS::RlsDynamics::centroidalAccelerationSynergy;

  map_motionController["rest_cmlC"] = &RLS::RlsDynamics::rest_cmlC;
  map_motionController["rest_clCm"] = &RLS::RlsDynamics::rest_clCm;
  map_motionController["baseGeneralizedMomentum"] = &RLS::RlsDynamics::baseGeneralizedMomentum;
  map_motionController["mixedGeneralizedMomentum"] = &RLS::RlsDynamics::mixedGeneralizedMomentum;
  map_motionController["accelerationSolver"] = &RLS::RlsDynamics::accelerationSolver;
  map_motionController["hogehogeMomentum"] = &RLS::RlsDynamics::hogehogeMomentum;

  // internal force controller
  // ****************************************************************
  map_internalForceController["default"] = &RLS::RlsDynamics::defaultController;
  map_internalForceController["m_internalDistribution"] = &RLS::RlsDynamics::m_internalDistribution;

  // force controller
  // ****************************************************************
  map_forceController["default"] = &RLS::RlsDynamics::defaultController;
  map_forceController["baseDistribution"] = &RLS::RlsDynamics::baseDistribution;
  map_forceController["centroidalDistribution"] = &RLS::RlsDynamics::centroidalDistribution;
  map_forceController["centroidalDcmDistribution"] = &RLS::RlsDynamics::centroidalDcmDistribution;
  map_forceController["centroidalEcmpDistribution"] = &RLS::RlsDynamics::centroidalEcmpDistribution;
  map_forceController["handWrenchControlAndCentroidalEcmpDistribution"] = &RLS::RlsDynamics::handWrenchControlAndCentroidalEcmpDistribution;

  map_forceController["distributionSolver"] = &RLS::RlsDynamics::distributionSolver;

  // torque controller
  // ****************************************************************
  map_torqueController["default"] = &RLS::RlsDynamics::defaultController;
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
  // ****************************************************************
  map_inverseDynamicsController["default"] = &RLS::RlsDynamics::defaultJointController;
  map_inverseDynamicsController["fullDynamicsController"] = &RLS::RlsDynamics::fullDynamicsController;
  map_inverseDynamicsController["momentumInverseDynamicsController"] = &RLS::RlsDynamics::momentumInverseDynamicsController;
  map_inverseDynamicsController["highGainController"] = &RLS::RlsDynamics::highGainController;
  map_inverseDynamicsController["spatialDynamicsSolver"] = &RLS::RlsDynamics::spatialDynamicsSolver;
  map_inverseDynamicsController["dlrSolver"] = &RLS::RlsDynamics::dlrSolver;

  map_externalWrenchController["default"] = &RLS::RlsDynamics::defaultController;
  map_externalWrenchController["transformExternalWrench"] = &RLS::RlsDynamics::transformExternalWrench;

  // extWrapper.setControllerMap(this);
}
