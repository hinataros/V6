/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::analysisYaml(const int &controllerID)
{
  if(debug) DEBUG;

  // initialize yamlInfo
  // ********************************
  yamlInfo.sequenceNum = 0;
  yamlInfo.sequence = 0;
  // ********************************

  YAML::Node doc = YAML::LoadFile(config.path_yaml_controller.c_str());

  if(doc["Controller"][controllerID])
    yamlInfo.doc.controllerKey = doc["Controller"][controllerID];
  else if(doc["Controller"])
    yamlInfo.doc.controllerKey = doc["Controller"];

  yamlInfo.doc.defaultKey = yamlInfo.doc.controllerKey["Default"];

  if(yamlInfo.doc.controllerKey["Sequence"][0].size()){
    if(yamlInfo.doc.controllerKey["Sequence"][0][0].size()){
      yamlInfo.sequenceNum = yamlInfo.doc.controllerKey["Sequence"].size();
      yamlInfo.doc.sequenceKey = new YAML::Node[yamlInfo.sequenceNum];

      for(int i=0; i<yamlInfo.sequenceNum; i++)
        yamlInfo.doc.sequenceKey[i] = yamlInfo.doc.controllerKey["Sequence"][i];
    }
    else{
      yamlInfo.sequenceNum = 1;
      yamlInfo.doc.sequenceKey = new YAML::Node[1];
      yamlInfo.doc.sequenceKey[0] = yamlInfo.doc.controllerKey["Sequence"];
    }
  }
  else{
    yamlInfo.doc.sequenceKey = new YAML::Node[0];
  }

  if(yamlInfo.doc.controllerKey["State"][0])
    yamlInfo.doc.stateKey = yamlInfo.doc.controllerKey["State"];

  sequence = new Sequence[yamlInfo.sequenceNum];

  for(int i=0; i<yamlInfo.sequenceNum; i++){
    sequence[i].phase = 0;
    sequence[i].tw0 = 0.;
    sequence[i].twf = 0.;
  }
}
