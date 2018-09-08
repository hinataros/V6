/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  string RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name1, string name2, string value)
  {
    if(multi){
      if(!checkNode(doc, node, num, phase, name1, name2))
        return value;

      return readValue<string>(doc, node, num, phase, name1, name2);
    }

    if(!checkNode(doc, node, phase, name1, name2))
      return value;

    return readValue<string>(doc, node, phase, name1, name2);
  }
  template<>
  int RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name1, string name2, int value)
  {
    if(multi){
      if(!checkNode(doc, node, num, phase, name1, name2))
        return value;

      return readValue<int>(doc, node, num, phase, name1, name2);
    }

    if(!checkNode(doc, node, phase, name1, name2))
      return value;

    return readValue<int>(doc, node, phase, name1, name2);
  }

  template<>
  Vector6d RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name1, string name2, Vector6d vec)
  {
    if(multi){
      if(doc[node][num][phase][name1][name2].size()==6)
        for(int i=0; i<6; i++)
          vec(i) = readValue<double>(doc, node, num, phase, name1, name2, i);
      else
        return vec;
    }
    else{
      if(doc[node][phase][name1][name2].size()==6)
        for(int i=0; i<6; i++)
          vec(i) = readValue<double>(doc, node, phase, name1, name2, i);
      else
        return vec;
    }

    return vec;
  }

  template<>
  Matrix2i RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name1, string name2, Matrix2i mat)
  {
    Matrix2i temp_mat = Matrix2i::Zero();

    if(multi){
      if(!checkNode(doc, node, num, phase, name1, name2))
        return mat;

      if(doc[node][num][phase][name1][name2].size()==0){
        return readValue<int>(doc, node, num, phase, name1, name2)*Matrix2i::Identity();
      }
      else if(doc[node][num][phase][name1][name2].size()==2){
        for(int i=0; i<2; i++)
          temp_mat(i,i) = readValue<int>(doc, node, num, phase, name1, name2, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name1, name2))
        return mat;

      if(doc[node][phase][name1][name2].size()==0){
        return readValue<int>(doc, node, phase, name1, name2)*Matrix2i::Identity();
      }
      else if(doc[node][phase][name1][name2].size()==2){
        for(int i=0; i<2; i++)
          temp_mat(i,i) = readValue<int>(doc, node, phase, name1, name2, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
  template<>
  Matrix6i RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name1, string name2, Matrix6i mat)
  {
    Matrix6i temp_mat = Matrix6i::Zero();

    if(multi){
      if(!checkNode(doc, node, num, phase, name1, name2))
        return mat;

      if(doc[node][num][phase][name1][name2].size()==0){
        return readValue<int>(doc, node, num, phase, name1, name2)*Matrix6i::Identity();
      }
      else if(doc[node][num][phase][name1][name2].size()==6){
        for(int i=0; i<6; i++)
          temp_mat(i,i) = readValue<int>(doc, node, num, phase, name1, name2, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name1, name2))
        return mat;

      if(doc[node][phase][name1][name2].size()==0){
        return readValue<int>(doc, node, phase, name1, name2)*Matrix6i::Identity();
      }
      else if(doc[node][phase][name1][name2].size()==6){
        for(int i=0; i<6; i++)
          temp_mat(i,i) = readValue<int>(doc, node, phase, name1, name2, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
  template<>
  Matrix6d RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name1, string name2, Matrix6d mat)
  {
    Matrix6d temp_mat = Matrix6d::Zero();

    if(multi){
      if(!checkNode(doc, node, num, phase, name1, name2))
        return mat;

      if(doc[node][num][phase][name1][name2].size()==0){
        return readValue<double>(doc, node, num, phase, name1, name2)*Matrix6d::Identity();
      }
      else if(doc[node][num][phase][name1][name2].size()==6){
        for(int i=0; i<6; i++)
          temp_mat(i,i) = readValue<double>(doc, node, num, phase, name1, name2, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name1, name2))
        return mat;

      if(doc[node][phase][name1][name2].size()==0){
        return readValue<double>(doc, node, phase, name1, name2)*Matrix6d::Identity();
      }
      else if(doc[node][phase][name1][name2].size()==6){
        for(int i=0; i<6; i++)
          temp_mat(i,i) = readValue<double>(doc, node, phase, name1, name2, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
}
