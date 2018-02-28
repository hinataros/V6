/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::objective(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd Fz = MatrixXd::Identity(2*info.value.joint, 2*info.value.joint);

  MatrixXd cal_S = MatrixXd::Zero(2*info.value.joint,6*info.value.joint);
  for(int i=0; i<info.value.joint; i++)
    cal_S.block(2*i,6*i+3,2,2) = bbSx;

  for(int i=0; i<info.value.joint; i++){
    Fz.block(2*i,2*i,2,2) *= cal_F(6*i+2);
  }

  Pc = pInv(Bp.transpose()*Fz*Bp)*Bp.transpose()*cal_S*Bc;

  return 0;
}
