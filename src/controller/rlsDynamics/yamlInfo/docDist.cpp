/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

YAML::Node RLS::YamlInfo::docDist()
{
  if(debug) DEBUG;

  YAML::Node doc = YAML::Clone(this->doc.controllerKey);

  controllerYamlModifier(doc);// amiyata yaml-cppの特性上中身ゴリッゴリに書き換えるから注意
  return doc;
}
