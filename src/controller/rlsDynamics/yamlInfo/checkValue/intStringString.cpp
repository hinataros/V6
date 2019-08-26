/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  bool RLS::YamlInfo::checkValue(int &value, const int num, const string name1, const string name2)
  {
    if(localKey[key][num][name1][name2])
      value = localKey[key][num][name1][name2].as<int>();
    else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(Vector3d &value, const int num, const string name1, const string name2)
  {
    unsigned size = 3;
    if(localKey[key][num][name1][name2]){
      if(localKey[key][num][name1][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][num][name1][name2].as<double>();

      if(localKey[key][num][name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][num][name1][name2][i].as<double>();
    }else
      return false;

    return true;
  }
}
