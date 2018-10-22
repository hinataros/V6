/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "yamlInfo.hpp"

namespace RLS{
  template<>
  void RLS::YamlInfo::checkUserValue(int &value, const string name1, const string name2)
  {
    if(doc.controllerKey[name1][name2])
      value = doc.controllerKey[name1][name2].as<int>();
  }
  template<>
  void RLS::YamlInfo::checkUserValue(double &value, const string name1, const string name2)
  {
    if(doc.controllerKey[name1][name2])
      value = doc.controllerKey[name1][name2].as<double>();
  }
  template<>
  void RLS::YamlInfo::checkUserValue(string &value, const string name1, const string name2)
  {
    if(doc.controllerKey[name1][name2])
      value = doc.controllerKey[name1][name2].as<string>();
  }

  template<>
  void RLS::YamlInfo::checkUserValue(Vector6d &value, const string name1, const string name2)
  {
    unsigned size = 6;

    if(doc.controllerKey[name1][name2])
      if(doc.controllerKey[name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i) = doc.controllerKey[name1][name2][i].as<double>();
  }

  template<>
  void RLS::YamlInfo::checkUserValue(Matrix2i &value, const string name1, const string name2)
  {
    unsigned size = 2;

    if(doc.controllerKey[name1][name2]){
      if(doc.controllerKey[name1][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name1][name2].as<int>();

      if(doc.controllerKey[name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name1][name2][i].as<int>();
    }
  }
  template<>
  void RLS::YamlInfo::checkUserValue(Matrix6i &value, const string name1, const string name2)
  {
    unsigned size = 6;

    if(doc.controllerKey[name1][name2]){
      if(doc.controllerKey[name1][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name1][name2].as<int>();

      if(doc.controllerKey[name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name1][name2][i].as<int>();
    }
  }
  template<>
  void RLS::YamlInfo::checkUserValue(Matrix6d &value, const string name1, const string name2)
  {
    unsigned size = 6;

    if(doc.controllerKey[name1][name2]){
      if(doc.controllerKey[name1][name2].size()==0)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name1][name2].as<double>();

      if(doc.controllerKey[name1][name2].size()==size)
        for(unsigned i=0; i<size; i++)
          value(i,i) = doc.controllerKey[name1][name2][i].as<double>();
    }
  }
}
