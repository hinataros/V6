/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  bool RLS::YamlInfo::checkValue(int &value, const int num, const string name)
  {
    if(localKey[key][num][name])
      value = localKey[key][num][name].as<int>();
    else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(Vector3d &value, const int num, const string name)
  {
    unsigned size = 3;
    if(localKey[key][num][name]){
      if(localKey[key][num][name].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][num][name].as<double>();

      if(localKey[key][num][name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][num][name][i].as<double>();
    }else
      return false;

    return true;
  }
}
