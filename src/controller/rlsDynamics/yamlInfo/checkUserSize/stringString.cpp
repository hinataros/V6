/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

int RLS::YamlInfo::checkUserSize(const string name1, const string name2)
{
  if(doc.controllerKey[name1][name2])
    return doc.controllerKey[name1][name2].size();
  else
    return 0;
}
