/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::mapping()
{
  if(debug) DEBUG;

  desiredBaseTranslationGenerator_ptr = map_desiredBaseTranslationGenerator[desiredBaseTranslationGeneratorName];
  desiredBaseOrientationGenerator_ptr = map_desiredBaseOrientationGenerator[desiredBaseOrientationGeneratorName];

  for(int i=0; i<info->controlNodeNum; i++){
    desiredControlNodeMotionGenerator_ptr[i] = map_desiredControlNodeMotionGenerator[i][desiredControlNodeMotionGeneratorName[i]];
    desiredControlNodeForceGenerator_ptr[i] = map_desiredControlNodeForceGenerator[i][desiredControlNodeForceGeneratorName[i]];
  }

  desiredComGenerator_ptr = map_desiredComGenerator[desiredComGeneratorName];
  desiredDcmGenerator_ptr = map_desiredDcmGenerator[desiredDcmGeneratorName];
  desiredExternalWrenchGenerator_ptr = map_desiredExternalWrenchGenerator[desiredExternalWrenchGeneratorName];
}
