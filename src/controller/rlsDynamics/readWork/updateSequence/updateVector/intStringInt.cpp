/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  VectorXd RlsDynamics::updateVector(YAML::Node &doc, bool multi, string node, int num, int phase, string name, int controlNodeNum, VectorXd vec)
  {
    VectorXd temp_vec = VectorXd::Zero(vec.size());

    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return vec;

      if(doc[node][num][phase][name].size()==controlNodeNum){
        int size = 0;
        for(int i=0; i<controlNodeNum; i++)
          size += doc[node][num][phase][name][i].size();
        if(vec.size() != size)
          return vec;

        for(int i=0, k=0; i<controlNodeNum; i++){
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

      if(doc[node][phase][name].size()==controlNodeNum){
        int size = 0;
        for(int i=0; i<controlNodeNum; i++)
          size += doc[node][phase][name][i].size();
        if(vec.size() != size)
          return vec;

        for(int i=0, k=0; i<controlNodeNum; i++){
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
}
