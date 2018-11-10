/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

void RLS::YamlInfo::initialize(const string &path_yaml_controller, const int &controllerID)
{
  if(debug) DEBUG;

  controllerKeyName = "controller";
  defaultKeyName = "default";
  sequenceKeyName = "sequence";
  stateKeyName = "state";

  angleUnit = "radian";

  sequenceNum = 0;
  sequence = 0;

  YAML::Node doc = YAML::LoadFile(path_yaml_controller.c_str());

  string angleUnitKeyName = "angle unit";
  if(doc[angleUnitKeyName])
    angleUnit = doc[angleUnitKeyName].as<string>();

  if(doc[controllerKeyName][controllerID])
    this->doc.controllerKey = doc[controllerKeyName][controllerID];
  else if(doc[controllerKeyName])
    this->doc.controllerKey = doc[controllerKeyName];

  this->doc.defaultKey = this->doc.controllerKey[defaultKeyName];

  if(this->doc.controllerKey[sequenceKeyName][0].size()){
    if(this->doc.controllerKey[sequenceKeyName][0][0].size()){
      sequenceNum = this->doc.controllerKey[sequenceKeyName].size();
      this->doc.sequenceKey = new YAML::Node[sequenceNum];

      for(int i=0; i<sequenceNum; i++)
        this->doc.sequenceKey[i] = this->doc.controllerKey[sequenceKeyName][i];
    }
    else{
      sequenceNum = 1;
      this->doc.sequenceKey = new YAML::Node[1];
      this->doc.sequenceKey[0] = this->doc.controllerKey[sequenceKeyName];
    }
  }
  else{
    this->doc.sequenceKey = new YAML::Node[0];
  }

  if(this->doc.controllerKey[stateKeyName][0])
    this->doc.stateKey = this->doc.controllerKey[stateKeyName];
}
