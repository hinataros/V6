/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeDesiredValueGeneratorMap(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  desiredBaseTranslationGeneratorNum = 0;
  desiredBaseOrientationGeneratorNum = 0;

  desiredControlNodeAccelerationGeneratorNum = new int[info.controlNodeNum];
  desiredControlNodeAccelerationGeneratorName = new string[info.controlNodeNum];
  for(int i=0; i<info.controlNodeNum; i++){
    desiredControlNodeAccelerationGeneratorNum[i] = 0;
    desiredControlNodeAccelerationGeneratorName[i] = "default";
  }

  desiredControlNodeWrenchGeneratorNum = new int[info.controlNodeNum];
  desiredControlNodeWrenchGeneratorName = new string[info.controlNodeNum];
  for(int i=0; i<info.controlNodeNum; i++){
    desiredControlNodeWrenchGeneratorNum[i] = 0;
    desiredControlNodeWrenchGeneratorName[i] = "default";
  }

  desiredComGeneratorNum = 0;
  desiredDcmGeneratorNum = 0;
  desiredExternalWrenchGeneratorNum = 0;

  desiredBaseTranslationGeneratorName
    = desiredBaseOrientationGeneratorName
    = desiredComGeneratorName
    = desiredDcmGeneratorName
    = desiredExternalWrenchGeneratorName
    = "default";

  // mapping
  // ********************************
  // base translation
  map_desiredBaseTranslationGenerator["default"] = &RLS::RlsDynamics::desiredBaseTranslationZeroGenerator;
  map_desiredBaseTranslationGenerator["CP"] = &RLS::RlsDynamics::desiredBaseTranslationGeneratorCP;

  // base orientation
  map_desiredBaseOrientationGenerator["default"] = &RLS::RlsDynamics::desiredBaseOrientationZeroGenerator;
  map_desiredBaseOrientationGenerator["CP"] = &RLS::RlsDynamics::desiredBaseOrientationGeneratorCP;

  // control node acceleration
  map_desiredControlNodeAccelerationGenerator = new map<string, void (RLS::RlsDynamics::*)(const int&, const double&)>[info.controlNodeNum];
  for(int i=0; i<info.controlNodeNum; i++){
    map_desiredControlNodeAccelerationGenerator[i]["default"] = &RLS::RlsDynamics::desiredControlNodeAccelerationZeroGenerator;
    map_desiredControlNodeAccelerationGenerator[i]["CP"] = &RLS::RlsDynamics::desiredControlNodeAccelerationGeneratorCP;
    map_desiredControlNodeAccelerationGenerator[i]["CPabs"] = &RLS::RlsDynamics::desiredControlNodeAccelerationGeneratorCPabs;
    map_desiredControlNodeAccelerationGenerator[i]["walking"] = &RLS::RlsDynamics::desiredControlNodeAccelerationGeneratorWalking;
  }

  // control node wrench
  map_desiredControlNodeWrenchGenerator = new map<string, void (RLS::RlsDynamics::*)(const int&, const double&)>[info.controlNodeNum];
  for(int i=0; i<info.controlNodeNum; i++){
    map_desiredControlNodeWrenchGenerator[i]["default"] = &RLS::RlsDynamics::desiredControlNodeWrenchZeroGenerator;
    map_desiredControlNodeWrenchGenerator[i]["CP"] = &RLS::RlsDynamics::desiredControlNodeWrenchGeneratorCP;
  }

  // com
  map_desiredComGenerator["default"] = &RLS::RlsDynamics::desiredComZeroGenerator;
  map_desiredComGenerator["CP"] = &RLS::RlsDynamics::desiredComGeneratorCP;

  // dcm
  map_desiredDcmGenerator["default"] = &RLS::RlsDynamics::desiredDcmZeroGenerator;
  map_desiredDcmGenerator["CP"] = &RLS::RlsDynamics::desiredDcmGeneratorCP;
  map_desiredDcmGenerator["HTWalking"] = &RLS::RlsDynamics::desiredDcmGeneratorHTWalking;

  // external wrench
  map_desiredExternalWrenchGenerator["default"] = &RLS::RlsDynamics::desiredExternalWrenchZeroGenerator;
  map_desiredExternalWrenchGenerator["CP"] = &RLS::RlsDynamics::desiredExternalWrenchGeneratorCP;

  desiredControlNodeAccelerationGenerator_ptr = (void (RLS::RlsDynamics::**)(const int&, const double&))malloc(sizeof(void (RLS::RlsDynamics::*)(const int&, const double&))*info.controlNodeNum);
  desiredControlNodeWrenchGenerator_ptr = (void (RLS::RlsDynamics::**)(const int&, const double&))malloc(sizeof(void (RLS::RlsDynamics::*)(const int&, const double&))*info.controlNodeNum);
}
