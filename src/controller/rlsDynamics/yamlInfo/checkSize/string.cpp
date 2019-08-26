/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"


int RLS::YamlInfo::checkSize(const string name)
{
  if(localKey[key][name])
    return localKey[key][name].size();
  else
    return 0;
}
