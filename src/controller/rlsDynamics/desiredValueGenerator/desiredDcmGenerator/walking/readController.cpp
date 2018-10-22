/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::readController()
{
  if(debug) DEBUG;

  yamlInfo->checkUserValue<int>(ht_config.stepNum, "Walking", "stepNum");

  yamlInfo->checkUserValue<double>(ht_config.dtstep, "Walking", "dtstep");
  yamlInfo->checkUserValue<double>(ht_config.dtDSstep, "Walking", "dtDSstep");
  yamlInfo->checkUserValue<double>(ht_config.alphaDSstep, "Walking", "alphaDSstep");
  yamlInfo->checkUserValue<double>(ht_config.alphaHTstep, "Walking", "alphaHTstep");
  yamlInfo->checkUserValue<double>(ht_config.offset, "Walking", "offset");
  yamlInfo->checkUserValue<double>(ht_config.toe, "Walking", "toe");
  yamlInfo->checkUserValue<double>(ht_config.heel, "Walking", "heel");
}
