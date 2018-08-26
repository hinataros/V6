/**
   @author Sho Miyahara 2017
   1/2 x^T G x + g^T x
   CE x = ce
   CI x >= ci
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::distributionSolver(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // // base
  // // ************************************************************************
  // // VectorXd rpkDes = VectorXd::Zero(2*info.contact.num);
  // VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);

  // MatrixXd G = Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // VectorXd g = -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  // MatrixXd CE = cal_Pc;
  // VectorXd ce = cal_dLBRef + cal_GB;

  // // ************************************************************************

  // mix
  // ************************************************************************
  // VectorXd rpkDes = VectorXd::Zero(2*info.contact.num);
  VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);

  MatrixXd G = Bc.transpose()*WF*Bc + Pc.transpose()*Bp.transpose()*Wp*Bp*Pc;

  VectorXd g = -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  MatrixXd CE = cal_PcM;
  VectorXd ce = cal_dLCRef + cal_GC;

  // ************************************************************************

  QuadProgpp::solver(G, g, "e", CE, ce, cal_FcBarRef);
}
