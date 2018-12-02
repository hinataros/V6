/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

void RLS::RlsDynamics::setControllerMap()
{
  if(debug) DEBUG;

  // momentum controller
  // ****************************************************************
  momentumController_map["default"] = &RLS::RlsDynamics::defaultController;
  momentumController_map["baseMomentum"] = &RLS::RlsDynamics::baseMomentum;
  momentumController_map["baseVrpMomentum"] = &RLS::RlsDynamics::baseVrpMomentum;
  momentumController_map["centroidalMomentum"] = &RLS::RlsDynamics::centroidalMomentum;
  momentumController_map["centroidalVrpMomentum"] = &RLS::RlsDynamics::centroidalVrpMomentum;
  momentumController_map["centroidalCmpMomentum"] = &RLS::RlsDynamics::centroidalCmpMomentum;

  // motion controller
  motionController_map["default"] = &RLS::RlsDynamics::defaultConfigurationController;

  // operational space reference
  // ****************************************************************
  // velocity controller
  operationalSpaceController_map["default"] = &RLS::RlsDynamics::defaultController;
  operationalSpaceController_map["relativeVelocityBaseMap"] = &RLS::RlsDynamics::relativeVelocityBaseMap;
  operationalSpaceController_map["relativeVelocityMixedMap"] = &RLS::RlsDynamics::relativeVelocityMixedMap;

  // acceleration controller
  operationalSpaceController_map["decomposeEndEffectorAcceleration"] = &RLS::RlsDynamics::decomposeEndEffectorAcceleration;
  operationalSpaceController_map["relativeAccelerationBaseMap"] = &RLS::RlsDynamics::relativeAccelerationBaseMap;
  operationalSpaceController_map["relativeAccelerationMixedMap"] = &RLS::RlsDynamics::relativeAccelerationMixedMap;
  operationalSpaceController_map["relativeAccelerationCentroidalMap"] = &RLS::RlsDynamics::relativeAccelerationCentroidalMap;

  // configuration space controller
  // ****************************************************************
  // velocity controller
  motionController_map["baseVelocitySynergy"] = &RLS::RlsDynamics::baseVelocitySynergy;
  motionController_map["mixedVelocitySynergy"] = &RLS::RlsDynamics::mixedVelocitySynergy;

  // acceleration controller
  motionController_map["workAcceleration"] = &RLS::RlsDynamics::workAcceleration;
  motionController_map["baseAccelerationSynergy"] = &RLS::RlsDynamics::baseAccelerationSynergy;
  motionController_map["mixedAccelerationSynergy"] = &RLS::RlsDynamics::mixedAccelerationSynergy;
  motionController_map["centroidalAccelerationSynergy"] = &RLS::RlsDynamics::centroidalAccelerationSynergy;

  motionController_map["rest_cmlC"] = &RLS::RlsDynamics::rest_cmlC;
  motionController_map["rest_clCm"] = &RLS::RlsDynamics::rest_clCm;
  motionController_map["baseGeneralizedMomentum"] = &RLS::RlsDynamics::baseGeneralizedMomentum;
  motionController_map["mixedGeneralizedMomentum"] = &RLS::RlsDynamics::mixedGeneralizedMomentum;
  motionController_map["accelerationSolver"] = &RLS::RlsDynamics::accelerationSolver;
  motionController_map["rcamd"] = &RLS::RlsDynamics::rcamd;

  // internal force controller
  // ****************************************************************
  internalForceController_map["default"] = &RLS::RlsDynamics::defaultController;
  internalForceController_map["m_internalDistribution"] = &RLS::RlsDynamics::m_internalDistribution;

  // force controller
  // ****************************************************************
  forceController_map["default"] = &RLS::RlsDynamics::defaultController;
  forceController_map["baseDistribution"] = &RLS::RlsDynamics::baseDistribution;
  forceController_map["centroidalDistribution"] = &RLS::RlsDynamics::centroidalDistribution;
  forceController_map["centroidalDcmDistribution"] = &RLS::RlsDynamics::centroidalDcmDistribution;
  forceController_map["centroidalEcmpDistribution"] = &RLS::RlsDynamics::centroidalEcmpDistribution;
  forceController_map["handWrenchControlAndCentroidalEcmpDistribution"] = &RLS::RlsDynamics::handWrenchControlAndCentroidalEcmpDistribution;

  forceController_map["distributionSolver"] = &RLS::RlsDynamics::distributionSolver;

  // torque controller
  // ****************************************************************
  torqueController_map["default"] = &RLS::RlsDynamics::defaultController;
  torqueController_map["jointSpace"] = &RLS::RlsDynamics::jointSpace;
  torqueController_map["staticControl"] = &RLS::RlsDynamics::staticControl;
  torqueController_map["base"] = &RLS::RlsDynamics::base;
  torqueController_map["mixed"] = &RLS::RlsDynamics::mixed;
  torqueController_map["mixedmixed"] = &RLS::RlsDynamics::mixedmixed;
  torqueController_map["crb"] = &RLS::RlsDynamics::crb;
  torqueController_map["baseOpt"] = &RLS::RlsDynamics::baseOpt;
  torqueController_map["mixedOpt"] = &RLS::RlsDynamics::mixedOpt;
  torqueController_map["mixedmixedOpt"] = &RLS::RlsDynamics::mixedmixedOpt;

  // inverse dynamics controller
  // ****************************************************************
  inverseDynamicsController_map["default"] = &RLS::RlsDynamics::defaultJointController;
  inverseDynamicsController_map["fullDynamicsController"] = &RLS::RlsDynamics::fullDynamicsController;
  inverseDynamicsController_map["momentumInverseDynamicsController"] = &RLS::RlsDynamics::momentumInverseDynamicsController;
  inverseDynamicsController_map["highGainController"] = &RLS::RlsDynamics::highGainController;
  inverseDynamicsController_map["spatialDynamicsSolver"] = &RLS::RlsDynamics::spatialDynamicsSolver;
  inverseDynamicsController_map["dlrSolver"] = &RLS::RlsDynamics::dlrSolver;

  externalWrenchController_map["default"] = &RLS::RlsDynamics::defaultController;
  externalWrenchController_map["transformExternalWrench"] = &RLS::RlsDynamics::transformExternalWrench;

  ext_momentumController_map["default"] = &RLS::Ext::defaultController;
  ext_motionController_map["default"] = &RLS::Ext::defaultConfigurationController;
  ext_forceController_map["default"] = &RLS::Ext::defaultController;
  ext_torqueController_map["default"] = &RLS::Ext::defaultController;
  ext_inverseDynamicsController_map["default"] = &RLS::Ext::defaultJointController;
  ext_externalWrenchController_map["default"] = &RLS::Ext::defaultController;
}
