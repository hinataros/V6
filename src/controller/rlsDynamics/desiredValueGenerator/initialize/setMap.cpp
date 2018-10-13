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
  map_desiredBaseTranslationGenerator["default"] = &RLS::DesiredValueGenerator::desiredBaseTranslationZeroGenerator;
  map_desiredBaseTranslationGenerator["CP"] = &RLS::DesiredValueGenerator::desiredBaseTranslationGeneratorCP;

  // base orientation
  map_desiredBaseOrientationGenerator["default"] = &RLS::DesiredValueGenerator::desiredBaseOrientationZeroGenerator;
  map_desiredBaseOrientationGenerator["CP"] = &RLS::DesiredValueGenerator::desiredBaseOrientationGeneratorCP;

  // control node acceleration
  map_desiredControlNodeMotionGenerator = new map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)>[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    map_desiredControlNodeMotionGenerator[i]["default"] = &RLS::DesiredValueGenerator::desiredControlNodeMotionZeroGenerator;
    map_desiredControlNodeMotionGenerator[i]["CP"] = &RLS::DesiredValueGenerator::desiredControlNodeMotionGeneratorCP;
    map_desiredControlNodeMotionGenerator[i]["CPabs"] = &RLS::DesiredValueGenerator::desiredControlNodeMotionGeneratorCPabs;
    map_desiredControlNodeMotionGenerator[i]["walking"] = &RLS::DesiredValueGenerator::desiredControlNodeMotionGeneratorWalking;
  }

  // control node wrench
  map_desiredControlNodeForceGenerator = new map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)>[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    map_desiredControlNodeForceGenerator[i]["default"] = &RLS::DesiredValueGenerator::desiredControlNodeForceZeroGenerator;
    map_desiredControlNodeForceGenerator[i]["CP"] = &RLS::DesiredValueGenerator::desiredControlNodeForceGeneratorCP;
  }

  // com
  map_desiredComGenerator["default"] = &RLS::DesiredValueGenerator::desiredComZeroGenerator;
  map_desiredComGenerator["CP"] = &RLS::DesiredValueGenerator::desiredComGeneratorCP;

  // dcm
  map_desiredDcmGenerator["default"] = &RLS::DesiredValueGenerator::desiredDcmZeroGenerator;
  map_desiredDcmGenerator["CP"] = &RLS::DesiredValueGenerator::desiredDcmGeneratorCP;
  // map_desiredDcmGenerator["HTWalking"] = &RLS::DesiredValueGenerator::desiredDcmGeneratorHTWalking;

  // external wrench
  map_desiredExternalWrenchGenerator["default"] = &RLS::DesiredValueGenerator::desiredExternalWrenchZeroGenerator;
  map_desiredExternalWrenchGenerator["CP"] = &RLS::DesiredValueGenerator::desiredExternalWrenchGeneratorCP;
}
