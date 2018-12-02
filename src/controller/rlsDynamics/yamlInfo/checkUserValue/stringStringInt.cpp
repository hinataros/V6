/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  bool RLS::YamlInfo::checkUserValue(Vector3d &value, const string name1, const string name2, const int num)
  {
    unsigned size = 3;

    if(doc.controllerKey[name1][name2][num]){
      if(doc.controllerKey[name1][name2][num].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = doc.controllerKey[name1][name2][num][i].as<double>();
    }else
      return false;

    return true;
  }
}
