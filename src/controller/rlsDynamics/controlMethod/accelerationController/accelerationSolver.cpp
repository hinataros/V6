/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::accelerationSolver(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // // base
  // // *********************************************************************************
  // MatrixXd Wq = MatrixXd::Zero(info.dof.all,info.dof.all);
  // Wq.block(6,6,info.dof.joint,info.dof.joint) = Wth;

  // MatrixXd G = cal_AB.transpose()*Wdh*cal_AB + Wq;
  // VectorXd g = -(cal_dLBRef - cal_CB).transpose()*Wdh*cal_AB;

  // int ceNum = info.contact.c.all + info.contact.m.all;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all);
  // CE <<
  //   Jc,
  //   Jm;

  // VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - dJm*dq;
  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -dJc*dq,
  //   dVmBarRef;
  // // *********************************************************************************

  // mix
  // *********************************************************************************
  MatrixXd Wq = MatrixXd::Zero(info.dof.all,info.dof.all);
  Wq.block(6,6,info.dof.joint,info.dof.joint) = Wth;

  MatrixXd G = cal_AM.transpose()*Wdh*cal_AM + Wq;
  VectorXd g = -(cal_dLCRef - cal_CM).transpose()*Wdh*cal_AM;

  int ceNum = info.contact.c.all + info.contact.m.all;
  MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all);
  CE <<
    JcM,
    JmM;

  VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - dJmM*dqM;
  VectorXd ce = VectorXd::Zero(ceNum);
  ce <<
    -dJcM*dqM,
    dVmBarRef;
  // *********************************************************************************
  // if(info.sim.state)
  //   QuadProgpp::solver(G, g, "e", CE, ce, ddqBoptRef);

  // return ddqBoptRef;

  // if(info.sim.state)
  //   QuadProgpp::solver(G, g, "e", CE, ce, ddqMoptRef);

  return ddqMoptRef;
}
