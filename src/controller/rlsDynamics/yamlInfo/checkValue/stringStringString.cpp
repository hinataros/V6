/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  void RLS::YamlInfo::checkValue(int &value, const string name1, const string name2, const string name3)
  {
    if(localKey[key][name1][name2][name3])
      value = localKey[key][name1][name2][name3].as<int>();
  }
  template<>
  void RLS::YamlInfo::checkValue(string &value, const string name1, const string name2, const string name3)
  {
    if(localKey[key][name1][name2][name3])
      value = localKey[key][name1][name2][name3].as<string>();
  }
}
