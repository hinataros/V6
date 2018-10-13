/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

void RLS::YamlInfo::initialize(const string &key, const int &sequence, const int &phase)
{
  this->key = key;

  // smiyahara: YAML::Nodeの謎の挙動のせい
  YAML::Node temp;

  if(key=="Default"){
    localKey["Default"] = doc.defaultKey;
  }
  else if(key=="Sequence"){
    this->sequence = sequence;
    temp[phase] = doc.sequenceKey[sequence][phase];
    localKey["Sequence"] = temp[phase];
  }
  else if(key=="State"){
    this->state = phase;
    temp[phase] = doc.stateKey[phase];
    localKey["State"] = temp[phase];
  }
  else{
    cout << manip_error("no such '"+key+"' key") << endl;
  }
}
