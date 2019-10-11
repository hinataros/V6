/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

VectorXd RLS::TreeModel::readJointState(string state)
{
  if(debug) DEBUG;

  VectorXd x = VectorXd(info->dof.joint);

  if(state=="joint angle"){
    for(int i=1, j=0; i<info->linkNum; i++){
      if(link[i].active){
        x(j) = link[i].th;
        j++;
      }
    }
  }else if(state=="joint velocity"){
    for(int i=1, j=0; i<info->linkNum; i++){
      if(link[i].active){
        x(j) = link[i].dth;
        j++;
      }
    }

  }else if(state=="initial joint angle"){
    for(int i=1, j=0; i<info->linkNum; i++){
      if(link[i].active){
        x(j) = link[i].th0;
        j++;
      }
    }
  }else if(state=="initial joint velocity"){
    for(int i=1, j=0; i<info->linkNum; i++){
      if(link[i].active){
        x(j) = link[i].dth0;
        j++;
      }
    }

  }else if(state=="rne torque"){
    for(int i=1, j=0; i<info->linkNum; i++){
      if(link[i].active){
        x(j) = link[i].tau_rne;
        j++;
      }
    }

  }else if(state=="maximum joint angle"){
    for(int i=1, j=0; i<info->linkNum; i++){
      if(link[i].active){
        x(j) = link[i].thMax;
        j++;
      }
    }
    
  }else if(state=="minimum joint angle"){
    for(int i=1, j=0; i<info->linkNum; i++){
      if(link[i].active){
        x(j) = link[i].thMin;
        j++;
      }
    }

  }else{
    cout << "no such state vector..." << endl;
  }

  return x;
}
