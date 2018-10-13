/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::resizeAll()
{
  if(debug) DEBUG;

  all.rC = Vector3d::Zero();
  all.vC = Vector3d::Zero();

  all.p = Vector3d::Zero();
  all.lC = Vector3d::Zero();

  all.Rk = MatrixXd::Zero(6*info->controlNodeNum, 6*info->controlNodeNum);
  all.dRk = MatrixXd::Zero(6*info->controlNodeNum, 6*info->controlNodeNum);
  all.TB2k = MatrixXd::Zero(6*info->controlNodeNum, 6);
  all.dTB2k = MatrixXd::Zero(6*info->controlNodeNum, 6);
  all.TC2k = MatrixXd::Zero(6*info->controlNodeNum, 6);
  all.dTC2k = MatrixXd::Zero(6*info->controlNodeNum, 6);

  all.J = MatrixXd::Zero(6*info->controlNodeNum, info->dof.joint);
  all.dJ = MatrixXd::Zero(6*info->controlNodeNum, info->dof.joint);

  all.M = MatrixXd::Zero(info->dof.all, info->dof.all);
  all.c = VectorXd::Zero(info->dof.all);
  all.g = VectorXd::Zero(info->dof.all);
  all.b = VectorXd::Zero(info->dof.all);

  all.dM = MatrixXd::Zero(info->dof.all, info->dof.all);

  all.JB2C = MatrixXd::Zero(3, info->dof.joint);
  all.dJB2C = MatrixXd::Zero(3, info->dof.joint);
  all.MM = MatrixXd::Zero(info->dof.all, info->dof.all);
  all.dMM = MatrixXd::Zero(info->dof.all, info->dof.all);

  // // output list
  // tm_list.posGifMatrix = MatrixXd::Zero(3, info->value.all);
}
