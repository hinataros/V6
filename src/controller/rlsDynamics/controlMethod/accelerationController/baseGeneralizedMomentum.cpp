/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::baseGeneralizedMomentum(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd AB = MatrixXd::Zero(6, info.dof.all);
  AB <<
    model.hoap2.all.M.block(0,0,6,info.dof.all);

  MatrixXd ABBar = MatrixXd::Zero(6+info.contact.c.all, info.dof.all);
  ABBar <<
    AB,
    Jc;

  MatrixXd dAB = MatrixXd::Zero(6, info.dof.all);
  dAB <<
    model.hoap2.all.dM.block(0,0,6,info.dof.all);

  MatrixXd dABBar = MatrixXd::Zero(6+info.contact.c.all, info.dof.all);
  dABBar <<
    dAB,
    dJc;

  VectorXd dq = VectorXd::Zero(info.dof.all);
  dq <<
    cal_VB,
    model.hoap2.all.dth;

  VectorXd cal_dLBBarRef = VectorXd::Zero(6+info.contact.c.all);
  cal_dLBBarRef.head(6) = cal_dLBRef;

  VectorXd ddqLBRef = pInv(ABBar)*(cal_dLBBarRef - dABBar*dq);

  // **********************************************************
  MatrixXd JmBar = Jm*N(ABBar);

  VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V;
  VectorXd dVmTildeRef = dVmBarRef - dJm*dq - Jm*ddqLBRef;

  VectorXd ddqmRef = N(ABBar)*pInv(JmBar)*dVmTildeRef;

  VectorXd ddqDRef = N(ABBar)*N(JmBar)*ddqD(config, info, model);

  ddqRef = ddqLBRef + ddqmRef + ddqDRef;

  // ddqRef = VectorXd::Zero(info.dof.all);

  return ddqRef;
}
