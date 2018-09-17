/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::writeJointStateVector(string state, VectorXd x)
{
  if(debug) DEBUG;

  if(info.dof.joint != x.size()){
    cout << "does not match joint state vector size..." << endl;
  }

  if(state=="joint angle"){
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].active){
        link[i].th = x(j);
        j++;
      }
    }
  }else if(state=="joint velocity"){
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].active){
         link[i].dth = x(j);
        j++;
      }
    }

  }else if(state=="rne joint acceleration"){
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].active){
        link[i].ddth_rne = x(j);
        j++;
      }
    }

  }else{
    cout << "no such state vector..." << endl;
  }
}
