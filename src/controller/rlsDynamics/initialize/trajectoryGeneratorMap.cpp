/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeTrajectoryGeneratorMap(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  baseTranslationTrajectoryNum = 0;
  baseOrientationTrajectoryNum = 0;

  controlNodeTrajectoryNum = new int[info.controlNodeNum];
  controlNodeTrajectoryName = new string[info.controlNodeNum];
  for(int i=0; i<info.controlNodeNum; i++){
    controlNodeTrajectoryNum[i] = 0;
    controlNodeTrajectoryName[i] = "default";
  }

  comTrajectoryNum = 0;
  dcmTrajectoryNum = 0;
  externalWrenchTrajectoryNum = 0;

  baseTranslationTrajectoryName
    = baseOrientationTrajectoryName
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

  map_controlNodeTrajectory = new map<string, void (RLS::RlsDynamics::*)(const int&, const double&)>[info.controlNodeNum];
  for(int i=0; i<info.controlNodeNum; i++){
    map_controlNodeTrajectory[i]["default"] = &RLS::RlsDynamics::controlNodeZeroTrajectory;
    map_controlNodeTrajectory[i]["CP"] = &RLS::RlsDynamics::controlNodeTrajectoryCP;
    map_controlNodeTrajectory[i]["walking"] = &RLS::RlsDynamics::controlNodeTrajectoryWalking;
  }

  // com
  map_comTrajectory["default"] = &RLS::RlsDynamics::comZeroTrajectory;
  map_comTrajectory["CP"] = &RLS::RlsDynamics::comTrajectoryCP;

  // dcm
  map_dcmTrajectory["default"] = &RLS::RlsDynamics::dcmZeroTrajectory;
  map_dcmTrajectory["CP"] = &RLS::RlsDynamics::dcmTrajectoryCP;
  map_dcmTrajectory["dcmHTWalking"] = &RLS::RlsDynamics::dcmHTWalking;

  // external wrench
  map_externalWrenchTrajectory["default"] = &RLS::RlsDynamics::externalWrenchZeroTrajectory;
  map_externalWrenchTrajectory["CP"] = &RLS::RlsDynamics::externalWrenchTrajectoryCP;

  controlNodeTrajectory_ptr = (void (RLS::RlsDynamics::**)(const int&, const double&))malloc(sizeof(void (RLS::RlsDynamics::*)(const int&, const double&))*info.controlNodeNum);
}
