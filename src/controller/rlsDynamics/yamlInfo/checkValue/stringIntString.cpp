/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template <>
  bool RLS::YamlInfo::checkValue<int>(int &value, const string name1, const int num, const string name2)
  {
    if(localKey[key][name1][num][name2])
      value = localKey[key][name1][num][name2].as<int>();
    else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue<double>(double &value, const string name1, const int num, const string name2)
  {
    if(localKey[key][name1][num][name2])
      value = localKey[key][name1][num][name2].as<double>();
    else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(Vector3d &value, const string name1, const int num, const string name2)
  {
    unsigned size = 3;
    if(localKey[key][name1][num][name2]){
      if(localKey[key][name1][num][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][name1][num][name2].as<double>();

      if(localKey[key][name1][num][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][name1][num][name2][i].as<double>();
    }else
      return false;

    return true;
  }
}
