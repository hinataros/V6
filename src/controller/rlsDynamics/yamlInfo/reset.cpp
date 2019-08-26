/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

void RLS::YamlInfo::reset()
{
  if(debug) DEBUG;

  string defaultKeyName = "default";

  this->key = defaultKeyName;
  localKey[defaultKeyName] = doc.defaultKey;
}

void RLS::YamlInfo::reset(YAML::Node doc)
{
  if(debug) DEBUG;

  string stateKeyName = "state";

  this->key = stateKeyName;

  // smiyahara: YAML::Nodeの謎の挙動のせい
  YAML::Node temp;

  temp[0] = doc;
  localKey[stateKeyName] = temp[0];
}
