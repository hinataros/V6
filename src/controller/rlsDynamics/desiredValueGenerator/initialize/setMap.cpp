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
  desiredBaseTranslationGenerator_map["default"] = &RLS::DesiredValueGenerator::desiredBaseTranslationZeroGenerator;
  desiredBaseTranslationGenerator_map["CP"] = &RLS::DesiredValueGenerator::desiredBaseTranslationGeneratorCP;

  // base orientation
  desiredBaseOrientationGenerator_map["default"] = &RLS::DesiredValueGenerator::desiredBaseOrientationZeroGenerator;
  desiredBaseOrientationGenerator_map["CP"] = &RLS::DesiredValueGenerator::desiredBaseOrientationGeneratorCP;

  // control node acceleration
  desiredControlNodeMotionGenerator_map = new map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)>[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    desiredControlNodeMotionGenerator_map[i]["default"] = &RLS::DesiredValueGenerator::desiredControlNodeMotionZeroGenerator;
    desiredControlNodeMotionGenerator_map[i]["CP"] = &RLS::DesiredValueGenerator::desiredControlNodeMotionGeneratorCP;
    desiredControlNodeMotionGenerator_map[i]["CPabs"] = &RLS::DesiredValueGenerator::desiredControlNodeMotionGeneratorCPabs;
    desiredControlNodeMotionGenerator_map[i]["walking"] = &RLS::DesiredValueGenerator::desiredControlNodeMotionGeneratorWalking;
  }

  // control node wrench
  desiredControlNodeForceGenerator_map = new map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)>[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    desiredControlNodeForceGenerator_map[i]["default"] = &RLS::DesiredValueGenerator::desiredControlNodeForceZeroGenerator;
    desiredControlNodeForceGenerator_map[i]["CP"] = &RLS::DesiredValueGenerator::desiredControlNodeForceGeneratorCP;
  }

  // com
  desiredComGenerator_map["default"] = &RLS::DesiredValueGenerator::desiredComZeroGenerator;
  desiredComGenerator_map["CP"] = &RLS::DesiredValueGenerator::desiredComGeneratorCP;

  // dcm
  desiredDcmGenerator_map["default"] = &RLS::DesiredValueGenerator::desiredDcmZeroGenerator;
  desiredDcmGenerator_map["CP"] = &RLS::DesiredValueGenerator::desiredDcmGeneratorCP;
  desiredDcmGenerator_map["HTWalking"] = &RLS::DesiredValueGenerator::dcmHTWalking;

  // external wrench
  desiredExternalWrenchGenerator_map["default"] = &RLS::DesiredValueGenerator::desiredExternalWrenchZeroGenerator;
  desiredExternalWrenchGenerator_map["CP"] = &RLS::DesiredValueGenerator::desiredExternalWrenchGeneratorCP;
}
