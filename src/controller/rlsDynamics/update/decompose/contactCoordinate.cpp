/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::contactCoordinate(Model &model)
{
  if(debug) DEBUG;

  for(int i=0; i<model.hoap2.info.controlNodeNum; i++){
    bb_Rk.block(6*i,6*i,3,3) =
      bb_Rk.block(6*i+3,6*i+3,3,3) = Matrix3d::Identity();

    bb_dRk.block(6*i,6*i,3,3) =
      bb_dRk.block(6*i+3,6*i+3,3,3) = Matrix3d::Zero();
  }
}
