/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::objective(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  MatrixXd Fz = MatrixXd::Identity(2*info.controlNodeNum, 2*info.controlNodeNum);

  MatrixXd cal_S = MatrixXd::Zero(2*info.controlNodeNum,6*info.controlNodeNum);
  for(int i=0; i<info.controlNodeNum; i++)
    cal_S.block(2*i,6*i+3,2,2) = bb_Spx;

  for(int i=0; i<info.controlNodeNum; i++){
    Fz.block(2*i,2*i,2,2) *= cal_F(6*i+2);
  }

  Pc = pInv(Bp.transpose()*Fz*Bp)*Bp.transpose()*cal_S*Bc;

  return 0;
}
