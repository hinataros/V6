/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::objective()
{
  if(debug) DEBUG;

  MatrixXd Fz = MatrixXd::Identity(2*info.model->controlNodeNum, 2*info.model->controlNodeNum);

  MatrixXd cal_S = MatrixXd::Zero(2*info.model->controlNodeNum,6*info.model->controlNodeNum);
  for(int i=0; i<info.model->controlNodeNum; i++)
    cal_S.block(2*i,6*i+3,2,2) = antiDiag(2, 1., -1.);

  for(int i=0; i<info.model->controlNodeNum; i++){
    Fz.block(2*i,2*i,2,2) *= model->cal_F(6*i+2);
  }

  if((Bp.transpose()*Fz*Bp).determinant())
    Pc = (Bp.transpose()*Fz*Bp).inverse()*Bp.transpose()*cal_S*Bc;
}
