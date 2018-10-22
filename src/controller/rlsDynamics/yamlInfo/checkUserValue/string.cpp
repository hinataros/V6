/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  void RLS::YamlInfo::checkUserValue(bool &value, const string name)
  {
    if(doc.controllerKey[name])
      value = doc.controllerKey[name].as<bool>();
  }
  template<>
  void RLS::YamlInfo::checkUserValue(int &value, const string name)
  {
    if(doc.controllerKey[name])
      value = doc.controllerKey[name].as<int>();
  }
  template<>
  void RLS::YamlInfo::checkUserValue(double &value, const string name)
  {
    if(doc.controllerKey[name])
      value = doc.controllerKey[name].as<double>();
  }
  template<>
  void RLS::YamlInfo::checkUserValue(string &value, const string name)
  {
    if(doc.controllerKey[name])
      value = doc.controllerKey[name].as<string>();
  }

  template<>
  void RLS::YamlInfo::checkUserValue(Vector3d &value, const string name)
  {
    unsigned size = 3;

    if(doc.controllerKey[name])
      if(doc.controllerKey[name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = doc.controllerKey[name][i].as<double>();
  }
  template<>
  void RLS::YamlInfo::checkUserValue(Vector6d &value, const string name)
  {
    unsigned size = 6;

    if(doc.controllerKey[name])
      if(doc.controllerKey[name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = doc.controllerKey[name][i].as<double>();
  }

  template<>
  void RLS::YamlInfo::checkUserValue(Matrix2d &value, const string name)
  {
    unsigned size = 2;

    if(doc.controllerKey[name]){
      if(doc.controllerKey[name].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name].as<double>();

      if(doc.controllerKey[name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name][i].as<double>();
    }
  }
  template<>
  void RLS::YamlInfo::checkUserValue(Matrix3d &value, const string name)
  {
    unsigned size = 3;

    if(doc.controllerKey[name]){
      if(doc.controllerKey[name].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name].as<double>();

      if(doc.controllerKey[name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name][i].as<double>();
    }
  }
  template<>
  void RLS::YamlInfo::checkUserValue(MatrixXd &value, const string name)
  {
    unsigned size = value.diagonal().size();

    if(doc.controllerKey[name]){
      if(doc.controllerKey[name].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name].as<double>();

      if(doc.controllerKey[name].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name][i].as<double>();
    }
  }
}
