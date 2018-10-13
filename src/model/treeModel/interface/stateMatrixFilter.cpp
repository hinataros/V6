/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

MatrixXd RLS::TreeModel::stateMatrixFilter(bool row, bool col, MatrixXd A)
{
  if(debug) DEBUG;

  MatrixXd x;

  if(row){
    if(col){
      MatrixXd temp = MatrixXd::Zero(info->dof.joint,A.cols());
      for(int i=1, j=0; i<info->linkNum; i++){
        if(link[i].active){
          temp.row(j) = A.row(i);
          j++;
        }
      }

      x = MatrixXd::Zero(info->dof.joint,info->dof.joint);
      for(int i=1, j=0; i<info->linkNum; i++){
        if(link[i].active){
          x.col(j) = temp.col(i);
          j++;
        }
      }
    }else{
      x = MatrixXd::Zero(info->dof.joint,A.cols());
      for(int i=1, j=0; i<info->linkNum; i++){
        if(link[i].active){
          x.row(j) = A.row(i);
          j++;
        }
      }
    }
  }else{
    if(col){
      x = MatrixXd::Zero(A.rows(),info->dof.joint);
      for(int i=1, j=0; i<info->linkNum; i++){
        if(link[i].active){
          x.col(j) = A.col(i);
          j++;
        }
      }
    }else{
      x = A;
    }
  }

  return x;
}
