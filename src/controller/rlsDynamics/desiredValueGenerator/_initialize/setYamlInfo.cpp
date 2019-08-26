/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::setYamlInfo(YamlInfo &yamlInfo)
{
  if(debug) DEBUG;

  this->yamlInfo = &yamlInfo;
  walking.setYamlInfo(yamlInfo); // amiyata
}
