/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  Vector3d RlsDynamics::updateVector(YAML::Node &doc, string node, int num, int phase, string name, Vector3d vec)
  {
    if(multiSequence){
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
  Vector6d RlsDynamics::updateVector(YAML::Node &doc, string node, int num, int phase, string name, Vector6d vec)
  {
    if(multiSequence){
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
  VectorXd RlsDynamics::updateVector(YAML::Node &doc, string node, int num, int phase, string name, int eeNum, VectorXd vec)
  {
    VectorXd temp_vec = VectorXd::Zero(vec.size());

    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name))
        return vec;

      if(doc[node][num][phase][name].size()==eeNum){
        int size = 0;
        for(int i=0; i<eeNum; i++)
          size += doc[node][num][phase][name][i].size();
        if(vec.size() != size)
          return vec;

        for(int i=0, k=0; i<eeNum; i++){
          size = doc[node][num][phase][name][i].size();
          for(int j=0; j<size; j++, k++)
            temp_vec(k) = readValue<double>(doc, node, num, phase, name, i, j);
        }

        return temp_vec;
      }
      else
        return vec;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return vec;

      if(doc[node][phase][name].size()==eeNum){
        int size = 0;
        for(int i=0; i<eeNum; i++)
          size += doc[node][phase][name][i].size();
        if(vec.size() != size)
          return vec;

        for(int i=0, k=0; i<eeNum; i++){
          size = doc[node][phase][name][i].size();
          for(int j=0; j<size; j++, k++){
            temp_vec(k) = readValue<double>(doc, node, phase, name, i, j);
          }
        }

        return temp_vec;
      }
    }

    return vec;
  }

  // template<> VectorXd RlsDynamics::updateVector(YAML::Node &doc, string node, int num, int phase, string name, VectorXd vec)
  // {
  //   if(multiSequence)
  //   // if(doc[node][seq][name].size())
  //     for(int i=0; i<vec.size(); i++)
  //       vec(i) = readValue<double>(doc, node, seq, name, i);

  //   else
  //     return vec;

  //   return vec;
  // }

}
