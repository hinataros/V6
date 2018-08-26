/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::baseGeneralizedMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  MatrixXd ABBar = MatrixXd::Zero(6+info.contact.c.all, info.dof.all);
  ABBar <<
    cal_AB,
    Jc;

  MatrixXd dABBar = MatrixXd::Zero(6+info.contact.c.all, info.dof.all);
  dABBar <<
    cal_dAB,
    dJc;

  VectorXd cal_dLBBarRef = VectorXd::Zero(6+info.contact.c.all);
  cal_dLBBarRef.head(6) = -cal_dLBRef;

  VectorXd ddqLBRef = pInv(ABBar)*(cal_dLBBarRef - dABBar*dq);

  // **********************************************************
  MatrixXd JmBar = Jm*N(ABBar);

  VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V;
  VectorXd dVmTildeRef = dVmBarRef - dJm*dq - Jm*ddqLBRef;

  VectorXd ddqmRef = N(ABBar)*pInv(JmBar)*dVmTildeRef;

  VectorXd ddqthDRef = N(ABBar)*N(JmBar)*ddqthD(info);

  ddqBoptRef = ddqLBRef + ddqmRef + ddqthDRef;

  return ddqBoptRef;
}
