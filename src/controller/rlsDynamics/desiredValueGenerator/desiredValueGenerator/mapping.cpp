/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::mapping()
{
  if(debug) DEBUG;

  desiredBaseTranslationGenerator_ptr = desiredBaseTranslationGenerator_map[desiredBaseTranslationGeneratorName];
  desiredBaseOrientationGenerator_ptr = desiredBaseOrientationGenerator_map[desiredBaseOrientationGeneratorName];

  for(int i=0; i<info->controlNodeNum; i++){
    desiredControlNodeMotionGenerator_ptr[i] = desiredControlNodeMotionGenerator_map[i][desiredControlNodeMotionGeneratorName[i]];
    desiredControlNodeForceGenerator_ptr[i] = desiredControlNodeForceGenerator_map[i][desiredControlNodeForceGeneratorName[i]];
  }

  desiredComGenerator_ptr = desiredComGenerator_map[desiredComGeneratorName];
  desiredDcmGenerator_ptr = desiredDcmGenerator_map[desiredDcmGeneratorName];
  desiredExternalWrenchGenerator_ptr = desiredExternalWrenchGenerator_map[desiredExternalWrenchGeneratorName];
}
