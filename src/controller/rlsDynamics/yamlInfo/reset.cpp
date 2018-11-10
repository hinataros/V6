/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

void RLS::YamlInfo::reset(const string &key, const int &sequence, const int &phase)
{
  string defaultKeyName = "default";
  string sequenceKeyName = "sequence";
  string stateKeyName = "state";

  this->key = key;

  // smiyahara: YAML::Nodeの謎の挙動のせい
  YAML::Node temp;

  if(key==defaultKeyName){
    localKey[defaultKeyName] = doc.defaultKey;
  }
  else if(key==sequenceKeyName){
    this->sequence = sequence;
    temp[phase] = doc.sequenceKey[sequence][phase];
    localKey[sequenceKeyName] = temp[phase];
  }
  else if(key==stateKeyName){
    this->state = phase;
    temp[phase] = doc.stateKey[phase];
    localKey[stateKeyName] = temp[phase];
  }
  else{
    cout << manip_error("no such '"+key+"' key") << endl;
  }
}
