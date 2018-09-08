/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  MatrixXd RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, int nodeNum, MatrixXd mat)
  {
    MatrixXd temp_mat = MatrixXd::Zero(mat.rows(),mat.cols());

    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==0){
        return readValue<double>(doc, node, num, phase, name)*MatrixXd::Identity(mat.rows(),mat.cols());
      }
      else if(doc[node][num][phase][name].size()==nodeNum){
        int size = 0;
        for(int i=0; i<nodeNum; i++)
          size += doc[node][num][phase][name][i].size();
        if(mat.diagonal().size() != size)
          return mat;

        for(int i=0, k=0; i<nodeNum; i++){
          size = doc[node][num][phase][name][i].size();
          for(int j=0; j<size; j++, k++)
            temp_mat(k,k) = readValue<double>(doc, node, num, phase, name, i, j);
        }

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==0){
        return readValue<double>(doc, node, phase, name)*MatrixXd::Identity(mat.rows(),mat.cols());
      }
      else if(doc[node][phase][name].size()==nodeNum){
        int size = 0;
        for(int i=0; i<nodeNum; i++)
          size += doc[node][phase][name][i].size();
        if(mat.diagonal().size() != size)
          return mat;

        for(int i=0, k=0; i<nodeNum; i++){
          size = doc[node][phase][name][i].size();
          for(int j=0; j<size; j++, k++)
            temp_mat(k,k) = readValue<double>(doc, node, phase, name, i, j);
        }

        return temp_mat;
      }
    }

    return mat;
  }
}
