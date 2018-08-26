/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeTrajectoryGeneratorMap()
{
  if(debug) DEBUG;

  baseTranslationTrajectoryNum = 0;
  baseOrientationTrajectoryNum = 0;
  endEffectorTrajectoryNum = 0;
  comTrajectoryNum = 0;
  dcmTrajectoryNum = 0;
  externalWrenchTrajectoryNum = 0;

  baseTranslationTrajectoryName
    = baseOrientationTrajectoryName
    = endEffectorTrajectoryName
    = comTrajectoryName
    = dcmTrajectoryName
    = externalWrenchTrajectoryName
    = "default";

  // mapping
  // ********************************
  // base translation
  map_baseTranslationTrajectory["default"] = &RLS::RlsDynamics::baseTranslationZeroTrajectory;
  map_baseTranslationTrajectory["CP"] = &RLS::RlsDynamics::baseTranslationTrajectoryCP;

  // base orientation
  map_baseOrientationTrajectory["default"] = &RLS::RlsDynamics::baseOrientationZeroTrajectory;
  map_baseOrientationTrajectory["CP"] = &RLS::RlsDynamics::baseOrientationTrajectoryCP;

  // end effector
  map_endEffectorTrajectory["default"] = &RLS::RlsDynamics::endEffectorZeroTrajectory;
  map_endEffectorTrajectory["CP"] = &RLS::RlsDynamics::endEffectorTrajectoryCP;

  // com
  map_comTrajectory["default"] = &RLS::RlsDynamics::comZeroTrajectory;
  map_comTrajectory["CP"] = &RLS::RlsDynamics::comTrajectoryCP;

  // dcm
  map_dcmTrajectory["default"] = &RLS::RlsDynamics::dcmZeroTrajectory;
  map_dcmTrajectory["CP"] = &RLS::RlsDynamics::dcmTrajectoryCP;

  // external wrench
  map_externalWrenchTrajectory["default"] = &RLS::RlsDynamics::externalWrenchZeroTrajectory;
  map_externalWrenchTrajectory["CP"] = &RLS::RlsDynamics::externalWrenchTrajectoryCP;
}
