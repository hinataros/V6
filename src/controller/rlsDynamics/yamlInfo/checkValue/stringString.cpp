/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  bool RLS::YamlInfo::checkValue(bool &value, const string name1, const string name2)
  {
    if(localKey[key][name1][name2])
      value = localKey[key][name1][name2].as<bool>();
    else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(int &value, const string name1, const string name2)
  {
    if(localKey[key][name1][name2])
      value = localKey[key][name1][name2].as<int>();
    else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(string &value, const string name1, const string name2)
  {
    if(localKey[key][name1][name2])
      value = localKey[key][name1][name2].as<string>();
    else
      return false;

    return true;
  }

  template<>
  bool RLS::YamlInfo::checkValue(Vector3d &value, const string name1, const string name2)
  {
    unsigned size = 3;

    if(localKey[key][name1][name2]){
      if(localKey[key][name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][name1][name2][i].as<double>();
    }else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(Vector6d &value, const string name1, const string name2)
  {
    unsigned size = 6;

    if(localKey[key][name1][name2]){
      if(localKey[key][name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][name1][name2][i].as<double>();
    }else
      return false;

    return true;
  }

  template<>
  bool RLS::YamlInfo::checkValue(Matrix2i &value, const string name1, const string name2)
  {
    unsigned size = 2;

    if(localKey[key][name1][name2]){
      if(localKey[key][name1][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name1][name2].as<int>();

      if(localKey[key][name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name1][name2][i].as<int>();
    }else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(Matrix6i &value, const string name1, const string name2)
  {
    unsigned size = 6;

    if(localKey[key][name1][name2]){
      if(localKey[key][name1][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name1][name2].as<int>();

      if(localKey[key][name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name1][name2][i].as<int>();
    }else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(Matrix3d &value, const string name1, const string name2)
  {
    unsigned size = 3;

    if(localKey[key][name1][name2]){
      if(localKey[key][name1][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name1][name2].as<double>();

      if(localKey[key][name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name1][name2][i].as<double>();
    }else
      return false;

    return true;
  }
  template<>
  bool RLS::YamlInfo::checkValue(Matrix6d &value, const string name1, const string name2)
  {
    unsigned size = 6;

    if(localKey[key][name1][name2]){
      if(localKey[key][name1][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name1][name2].as<double>();

      if(localKey[key][name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name1][name2][i].as<double>();
    }else
      return false;

    return true;
  }
}
