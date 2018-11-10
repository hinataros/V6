/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::readController()
{
  if(debug) DEBUG;

  string walkingKeyName = "walking";

  yamlInfo->checkUserValue<int>(ht_config.stepNum, walkingKeyName, "stepNum");

  yamlInfo->checkUserValue<double>(ht_config.dtstep, walkingKeyName, "dtstep");
  yamlInfo->checkUserValue<double>(ht_config.dtDSstep, walkingKeyName, "dtDSstep");
  yamlInfo->checkUserValue<double>(ht_config.alphaDSstep, walkingKeyName, "alphaDSstep");
  yamlInfo->checkUserValue<double>(ht_config.alphaHTstep, walkingKeyName, "alphaHTstep");
  yamlInfo->checkUserValue<double>(ht_config.offset, walkingKeyName, "offset");
  yamlInfo->checkUserValue<double>(ht_config.toe, walkingKeyName, "toe");
  yamlInfo->checkUserValue<double>(ht_config.heel, walkingKeyName, "heel");

  yamlInfo->checkUserValue<double>(ht_config.tstab, walkingKeyName, "tstab");
}
