/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::resize()
{
  if(debug) DEBUG;

  Bc_kDiag = MatrixXi::Zero(6*info.model->controlNodeNum, 6*info.model->controlNodeNum);
  Bm_kDiag = MatrixXi::Zero(6*info.model->controlNodeNum, 6*info.model->controlNodeNum);

  BpDiag = MatrixXi::Zero(2*info.model->controlNodeNum, 2*info.model->controlNodeNum);

  // selective matrix for forward kinematics
  bb_ScB = Matrix6d::Zero();
}
