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

  yamlInfo->checkUserValue<double>(ht_config.dtstep, walkingKeyName, "dtstep");
  yamlInfo->checkUserValue<double>(ht_config.dtDSstep, walkingKeyName, "dtDSstep");
  yamlInfo->checkUserValue<double>(ht_config.alphaDSstep, walkingKeyName, "alphaDSstep");
  yamlInfo->checkUserValue<double>(ht_config.alphaHTstep, walkingKeyName, "alphaHTstep");
  yamlInfo->checkUserValue<double>(ht_config.offset, walkingKeyName, "offset");
  yamlInfo->checkUserValue<double>(ht_config.toe, walkingKeyName, "toe");
  yamlInfo->checkUserValue<double>(ht_config.heel, walkingKeyName, "heel");
  yamlInfo->checkUserValue<double>(ht_config.zOsc, walkingKeyName, "oscillation"); // amiyata

  yamlInfo->checkUserValue<double>(ht_config.tstab, walkingKeyName, "tstab");

  vwpNum = yamlInfo->checkUserSize(walkingKeyName, "vrp waypoint");
  vwp = new Vector3d[vwpNum];
  for(int i=0; i<vwpNum; i++)
    yamlInfo->checkUserValue<Vector3d>(vwp[i], walkingKeyName, "vrp waypoint", i);
}
