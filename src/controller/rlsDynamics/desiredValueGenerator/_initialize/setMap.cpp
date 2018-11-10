/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::setMap()
{
  if(debug) DEBUG;

  // base translation
  baseTranslation_map["default"] = &RLS::DesiredValueGenerator::baseTranslationDefault;
  baseTranslation_map["CP"] = &RLS::DesiredValueGenerator::baseTranslationCP;

  // base orientation
  baseRotation_map["default"] = &RLS::DesiredValueGenerator::baseRotationDefault;
  baseRotation_map["CP"] = &RLS::DesiredValueGenerator::baseRotationCP;

  // control node translation
  controlNodeTranslation_map =
    new map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)>[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    controlNodeTranslation_map[i]["default"] = &RLS::DesiredValueGenerator::controlNodeTranslationDefault;
    controlNodeTranslation_map[i]["CP"] = &RLS::DesiredValueGenerator::controlNodeTranslationCP;
    controlNodeTranslation_map[i]["CPabs"] = &RLS::DesiredValueGenerator::controlNodeTranslationCPabs;
    controlNodeTranslation_map[i]["swing"] = &RLS::DesiredValueGenerator::controlNodeTranslationSwing;
  }

  // control node rotation
  controlNodeRotation_map =
    new map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)>[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    controlNodeRotation_map[i]["default"] = &RLS::DesiredValueGenerator::controlNodeRotationDefault;
    controlNodeRotation_map[i]["CP"] = &RLS::DesiredValueGenerator::controlNodeRotationCP;
    controlNodeRotation_map[i]["CPabs"] = &RLS::DesiredValueGenerator::controlNodeRotationCPabs;
  }

  // control node force
  controlNodeForce_map =
    new map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)>[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    controlNodeForce_map[i]["default"] = &RLS::DesiredValueGenerator::controlNodeForceDefault;
    controlNodeForce_map[i]["CP"] = &RLS::DesiredValueGenerator::controlNodeForceCP;
  }

  // control node moment
  controlNodeMoment_map =
    new map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)>[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    controlNodeMoment_map[i]["default"] = &RLS::DesiredValueGenerator::controlNodeMomentDefault;
    controlNodeMoment_map[i]["CP"] = &RLS::DesiredValueGenerator::controlNodeMomentCP;
  }

  // com
  com_map["default"] = &RLS::DesiredValueGenerator::comDefault;
  com_map["CP"] = &RLS::DesiredValueGenerator::comCP;

  // dcm
  dcm_map["default"] = &RLS::DesiredValueGenerator::dcmDefault;
  dcm_map["CP"] = &RLS::DesiredValueGenerator::dcmCP;
  dcm_map["HTWalking"] = &RLS::DesiredValueGenerator::dcmHTWalking;

  // external wrench
  externalWrench_map["default"] = &RLS::DesiredValueGenerator::externalWrenchDefault;
  externalWrench_map["CP"] = &RLS::DesiredValueGenerator::externalWrenchCP;
}
