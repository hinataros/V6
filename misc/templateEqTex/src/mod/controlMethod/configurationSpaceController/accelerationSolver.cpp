/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::accelerationSolver()
{
  if(debug) DEBUG;

  // // base
  // // *********************************************************************************
  // MatrixXd Wq = MatrixXd::Zero(info.model.dof.all,info.model.dof.all);
  // Wq.block(6,6,info.model.dof.joint,info.model.dof.joint) = Wth;

  // MatrixXd G = cal_AB.transpose()*Wdh*cal_AB + Wq;
  // VectorXd g = -(cal_dLBRef - cal_CB).transpose()*Wdh*cal_AB;

  // int ceNum = info.contact.c.all + info.contact.m.all;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all);
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
  MatrixXd Wq = MatrixXd::Zero(info.model.dof.all,info.model.dof.all);
  Wq.block(6,6,info.model.dof.joint,info.model.dof.joint) = Wth;

  MatrixXd G = model->cal_AM.transpose()*Wdh*model->cal_AM + Wq;
  VectorXd g = -(cal_dLCRef - model->cal_CM).transpose()*Wdh*model->cal_AM;

  int ceNum = info.constraint->c.all + info.constraint->m.all;
  MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all);
  CE <<
    constraintModel.JcM,
    constraintModel.JmM;

  VectorXd dVmBarRef = cal_dVmBarRef + constraintModel.dBm.transpose()*model->cal_V - constraintModel.dJmM*model->dqM;
  VectorXd ce = VectorXd::Zero(ceNum);
  ce <<
    -constraintModel.dJcM*model->dqM,
    dVmBarRef;
  // *********************************************************************************
  // if(info.model.sim.state)
  //   QuadProgpp::solver(G, g, "e", CE, ce, ddqBoptRef);

  // return ddqBoptRef;

  // if(info.model.sim.state)
  //   QuadProgpp::solver(G, g, "e", CE, ce, ddqMoptRef);

  return ddqMoptRef;
}
