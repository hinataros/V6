/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

YAML::Node RLS::YamlInfo::docDist()
{
  if(debug) DEBUG;

  return this->doc.controllerKey;
}
