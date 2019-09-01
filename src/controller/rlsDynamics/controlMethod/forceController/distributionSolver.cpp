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

  // MatrixXd CE = cal_Pc;
  // VectorXd ce = cal_dLBRef + model->cal_GB;

  // // ************************************************************************

  // mix
  // ************************************************************************
  // VectorXd rpkDes = VectorXd::Zero(2*info.constraint.num);
  VectorXd rpkDes = VectorXd::Zero(2*constraintModel.BpDiag.diagonal().sum()/2);

  MatrixXd G = constraintModel.Bc.transpose()*WF*constraintModel.Bc + constraintModel.Pc.transpose()*constraintModel.Bp.transpose()*Wp*constraintModel.Bp*constraintModel.Pc;

  VectorXd g = -rpkDes.transpose()*constraintModel.Bp.transpose()*Wp*constraintModel.Bp*constraintModel.Pc;

  MatrixXd CE = constraintModel.cal_PcM;
  VectorXd ce = cal_dLCRef + model->cal_GC;

  MatrixXd CI = MatrixXd::Zero(info.constraint->c.all,info.constraint->c.all);
  VectorXd ci = VectorXd::Zero(info.constraint->c.all);
  for(int i=0; i<info.constraint->c.all; i+=6){
    CI(i+2,i+2) = 1;
    ci(i+2) = 1.e-3;
  }

  // ************************************************************************

  QuadProgpp::solver(G, g, "e", CE, ce, cal_FcBarRef);
  // CFSQP::solver(G, g, "e", CE, ce, cal_FcBarRef);
}
