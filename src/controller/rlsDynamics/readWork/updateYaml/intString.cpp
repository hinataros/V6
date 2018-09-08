/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  string RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, string value)
  {
    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return value;

      return readValue<string>(doc, node, num, phase, name);
    }

    if(!checkNode(doc, node, phase, name))
      return value;

    return readValue<string>(doc, node, phase, name);
  }
  template<>
  double RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, double value)
  {
    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return value;

      return readValue<double>(doc, node, num, phase, name);
    }

    if(!checkNode(doc, node, phase, name))
      return value;

    return readValue<double>(doc, node, phase, name);
  }

  template<>
  Vector3d RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, Vector3d vec)
  {
    if(multi){
      if(doc[node][num][phase][name].size()==3)
        for(int i=0; i<3; i++)
          vec(i) = readValue<double>(doc, node, num, phase, name, i);
      else
        return vec;
    }
    else{
      if(doc[node][phase][name].size()==3)
        for(int i=0; i<3; i++)
          vec(i) = readValue<double>(doc, node, phase, name, i);
      else
        return vec;
    }

    return vec;
  }
  template<>
  Vector6d RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, Vector6d vec)
  {
    if(multi){
      if(doc[node][num][phase][name].size()==6)
        for(int i=0; i<6; i++)
          vec(i) = readValue<double>(doc, node, num, phase, name, i);
      else
        return vec;
    }
    else{
      if(doc[node][phase][name].size()==6)
        for(int i=0; i<6; i++)
          vec(i) = readValue<double>(doc, node, phase, name, i);
      else
        return vec;
    }

    return vec;
  }

  template<>
  Matrix2d RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, Matrix2d mat)
  {
    Matrix2d temp_mat = Matrix2d::Zero();

    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==0){
        return readValue<double>(doc, node, num, phase, name)*Matrix2d::Identity();
      }
      else if(doc[node][num][phase][name].size()==2){
        for(int i=0; i<2; i++)
          temp_mat(i,i) = readValue<double>(doc, node, num, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==0){
        return readValue<double>(doc, node, phase, name)*Matrix2d::Identity();
      }
      else if(doc[node][phase][name].size()==2){
        for(int i=0; i<2; i++)
          temp_mat(i,i) = readValue<double>(doc, node, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
  template<>
  Matrix3d RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, Matrix3d mat)
  {
    Matrix3d temp_mat = Matrix3d::Zero();

    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==0){
        return readValue<double>(doc, node, num, phase, name)*Matrix3d::Identity();
      }
      else if(doc[node][num][phase][name].size()==3){
        for(int i=0; i<3; i++)
          temp_mat(i,i) = readValue<double>(doc, node, num, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==0){
        return readValue<double>(doc, node, phase, name)*Matrix3d::Identity();
      }
      else if(doc[node][phase][name].size()==3){
        for(int i=0; i<3; i++)
          temp_mat(i,i) = readValue<double>(doc, node, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
  template<>
  Matrix6d RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, Matrix6d mat)
  {
    Matrix6d temp_mat = Matrix6d::Zero();

    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==0){
        return readValue<double>(doc, node, num, phase, name)*Matrix6d::Identity();
      }
      else if(doc[node][num][phase][name].size()==6){
        for(int i=0; i<6; i++)
          temp_mat(i,i) = readValue<double>(doc, node, num, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==0){
        return readValue<double>(doc, node, phase, name)*Matrix6d::Identity();
      }
      else if(doc[node][phase][name].size()==6){
        for(int i=0; i<6; i++)
          temp_mat(i,i) = readValue<double>(doc, node, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
}
