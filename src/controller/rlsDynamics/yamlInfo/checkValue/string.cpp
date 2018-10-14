/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  void RLS::YamlInfo::checkValue(bool &value, const string name)
  {
    if(localKey[key][name])
      value = localKey[key][name].as<bool>();
  }
  template<>
  void RLS::YamlInfo::checkValue(double &value, const string name)
  {
    if(localKey[key][name])
      value = localKey[key][name].as<double>();
  }
  template<>
  void RLS::YamlInfo::checkValue(string &value, const string name)
  {
    if(localKey[key][name])
      value = localKey[key][name].as<string>();
  }

  template<>
  void RLS::YamlInfo::checkValue(Vector3d &value, const string name)
  {
    unsigned size = 3;

    if(localKey[key][name])
      if(localKey[key][name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][name][i].as<double>();
  }
  template<>
  void RLS::YamlInfo::checkValue(Vector6d &value, const string name)
  {
    unsigned size = 6;

    if(localKey[key][name])
      if(localKey[key][name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = localKey[key][name][i].as<double>();
  }

  template<>
  void RLS::YamlInfo::checkValue(Matrix2d &value, const string name)
  {
    unsigned size = 2;

    if(localKey[key][name]){
      if(localKey[key][name].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name].as<double>();

      if(localKey[key][name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name][i].as<double>();
    }
  }
  template<>
  void RLS::YamlInfo::checkValue(Matrix3d &value, const string name)
  {
    unsigned size = 3;

    if(localKey[key][name]){
      if(localKey[key][name].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name].as<double>();

      if(localKey[key][name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name][i].as<double>();
    }
  }
  template<>
  void RLS::YamlInfo::checkValue(MatrixXd &value, const string name)
  {
    unsigned size = value.diagonal().size();

    if(localKey[key][name]){
      if(localKey[key][name].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name].as<double>();

      if(localKey[key][name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = localKey[key][name][i].as<double>();
    }
  }
}
