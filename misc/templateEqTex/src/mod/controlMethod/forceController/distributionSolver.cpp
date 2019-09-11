/**
   @author Sho Miyahara 2018
   1/2 x^T G x + g^T x
   CE x = ce
   CI x >= ci
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::distributionSolver()
{
  if(debug) DEBUG;

  // // base
  // // ************************************************************************
  // // VectorXd rpkDes = VectorXd::Zero(2*info.constraint.num);
  // VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);

  // MatrixXd G = Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // VectorXd g = -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  // MatrixXd CE = mbb_Cc;
  // VectorXd ce = cal_dLBRef + model->cal_GB;

  // // ************************************************************************

  // mix
  // ************************************************************************
  // VectorXd rpkDes = VectorXd::Zero(2*info.constraint.num);
  VectorXd rpkDes = VectorXd::Zero(2*constraintModel.BpDiag.diagonal().sum()/2);

  MatrixXd G = constraintModel.Bc.transpose()*WF*constraintModel.Bc + constraintModel.Pc.transpose()*constraintModel.Bp.transpose()*Wp*constraintModel.Bp*constraintModel.Pc;

  VectorXd g = -rpkDes.transpose()*constraintModel.Bp.transpose()*Wp*constraintModel.Bp*constraintModel.Pc;

  MatrixXd CE = constraintModel.mbb_CcM;
  VectorXd ce = cal_dLCRef + model->cal_GC;

  // ************************************************************************

  QuadProgpp::solver(G, g, "e", CE, ce, cal_FcBarRef);
}
