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

  yamlInfo->checkValue<double>(ht_config.dtstep, walkingKeyName, "dtstep");
  yamlInfo->checkValue<double>(ht_config.dtDSstep, walkingKeyName, "dtDSstep");
  yamlInfo->checkValue<double>(ht_config.alphaDSstep, walkingKeyName, "alphaDSstep");
  yamlInfo->checkValue<double>(ht_config.alphaHTstep, walkingKeyName, "alphaHTstep");
  yamlInfo->checkValue<double>(ht_config.offset, walkingKeyName, "offset");
  yamlInfo->checkValue<double>(ht_config.toe, walkingKeyName, "toe");
  yamlInfo->checkValue<double>(ht_config.heel, walkingKeyName, "heel");
  // amiyata ****
  if(yamlInfo->checkValue<double>(ht_config.zOsc, walkingKeyName, "oscillation")){
    oscF = true;
  } else {
    oscF = false;
  }
  yamlInfo->checkValue<int>(ht_config.ipDim, walkingKeyName, "ipDim");

  yamlInfo->checkValue<double>(ht_config.tstab, walkingKeyName, "tstab");

  // ***************************************************** // amiyata vrp way point abolition
  string sequenceKeyName = "sequence"; // load from sequence

  Vector6d vwpTemp;
  Vector3d rtemp, xitemp;
  string name[2] = {"RLEGEE", "LLEGEE"};

  // o("test");
  // rtemp = Vector3d::Zero();
  // yamlInfo->checkValue<Vector3d>(rtemp, sequenceKeyName, 2, "rf", "LLEGEE");
  // o(rtemp);

  for(int i=0; i<yamlInfo->checkSize(sequenceKeyName); i++){
    vwpTemp = Vector6d::Zero();
    // if(yamlInfo->checkValue<Vector3d>(rtemp, i, "rXf") || yamlInfo->checkValue<Vector3d>(rtemp, i, "rCf")){
    if(yamlInfo->checkValue<Vector3d>(rtemp, sequenceKeyName, i, "rXf")){
      vwpTemp.head(3) = rtemp - rX0;
      vwpTemp(2) = 0.;
      // o(rX0);
      vwp.push_back(vwpTemp);
      break;
    }
    else if(yamlInfo->checkValue<Vector3d>(rtemp, sequenceKeyName, i, "rXfabs")){
      vwpTemp.head(3) = rtemp;
      vwpTemp(2) = 0.;
      // o(rX0);
      vwp.push_back(vwpTemp);
      break;
    }

    for(int j=0; j<2; j++){ // RLEGEE or LLEGEE only
      rtemp = xitemp = Vector3d::Zero();
      if(yamlInfo->checkValue<Vector3d>(rtemp, sequenceKeyName, i, "rf", name[j])){
        yamlInfo->checkValue<Vector3d>(xitemp, sequenceKeyName, i, "xif", name[j]);
        if(yamlInfo->angleUnit=="degree")
          xitemp *= DEG2RAD;
        vwpTemp <<
          rtemp,
          xitemp;
        vwpTemp += rxw0.segment(j*6,6); // relative
        vwpTemp(2) = 0.; // これだけは補正
        vwp.push_back(vwpTemp);
      }
      else if(yamlInfo->checkValue<Vector3d>(rtemp, sequenceKeyName, i, "rfabs", name[j])){
        yamlInfo->checkValue<Vector3d>(xitemp, sequenceKeyName, i, "xifabs", name[j]);
        if(yamlInfo->angleUnit=="degree")
          xitemp *= DEG2RAD;
        vwpTemp <<
          rtemp,
          xitemp;
        vwpTemp(2) = 0.; // これだけは補正
        vwp.push_back(vwpTemp);
      }
    }
  }

  vwpNum = vwp.size();
}
