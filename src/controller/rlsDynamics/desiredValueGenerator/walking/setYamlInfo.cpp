/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setYamlInfo(YamlInfo &yamlInfo)
{
  if(debug) DEBUG;

  this->yamlInfo = &yamlInfo;
}
