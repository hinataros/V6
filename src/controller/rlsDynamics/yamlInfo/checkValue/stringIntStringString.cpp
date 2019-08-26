/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  bool RLS::YamlInfo::checkValue(int &value, const string name1, const int num, const string name2, const string name3)
  {
    if(localKey[key][name1][num][name2][name3])
      value = localKey[key][name1][num][name2][name3].as<int>();
    else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(double &value, const string name1, const int num, const string name2, const string name3)
  {
    if(localKey[key][name1][num][name2][name3])
      value = localKey[key][name1][num][name2][name3].as<double>();
    else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(Vector3d &value, const string name1, const int num, const string name2, const string name3)
  {
    unsigned size = 3;
    if(localKey[key][name1][num][name2][name3]){
      if(localKey[key][name1][num][name2][name3].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][name1][num][name2][name3].as<double>();

      if(localKey[key][name1][num][name2][name3].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][name1][num][name2][name3][i].as<double>();
    }else
      return false;

    return true;
  }
}
