/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::mapping()
{
  if(debug) DEBUG;

  baseTranslation_ptr = baseTranslation_map[baseTranslationName];
  baseRotation_ptr = baseRotation_map[baseRotationName];

  for(int i=0; i<info->controlNodeNum; i++){
    controlNodeTranslation_ptr[i] = controlNodeTranslation_map[i][controlNodeTranslationName[i]];
    controlNodeRotation_ptr[i] = controlNodeRotation_map[i][controlNodeRotationName[i]];
    controlNodeForce_ptr[i] = controlNodeForce_map[i][controlNodeForceName[i]];
    controlNodeMoment_ptr[i] = controlNodeMoment_map[i][controlNodeMomentName[i]];
  }

  com_ptr = com_map[comName];
  dcm_ptr = dcm_map[dcmName];
  externalWrench_ptr = externalWrench_map[externalWrenchName];
}
