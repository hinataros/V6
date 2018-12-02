/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::baseGeneralizedMomentum()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  MatrixXd ABBar = MatrixXd::Zero(6+info.constraint->c.all, info.model.dof.all);
  ABBar <<
    model->cal_AB,
    constraintModel.Jc;

  MatrixXd dABBar = MatrixXd::Zero(6+info.constraint->c.all, info.model.dof.all);
  dABBar <<
    model->cal_dAB,
    constraintModel.dJc;

  VectorXd cal_dLBBarRef = VectorXd::Zero(6+info.constraint->c.all);
  cal_dLBBarRef.head(6) = -cal_dLBRef;

  VectorXd ddqLBRef = pInv(ABBar)*(cal_dLBBarRef - dABBar*model->dq);

  // **********************************************************
  MatrixXd JmBar = constraintModel.Jm*N(ABBar);

  VectorXd dVmHatRef = cal_dVmBarRef + constraintModel.dBm.transpose()*model->cal_V;
  VectorXd dVmTildeRef = dVmHatRef - constraintModel.dJm*model->dq - constraintModel.Jm*ddqLBRef;

  VectorXd ddqmRef = N(ABBar)*pInv(JmBar)*dVmTildeRef;

  VectorXd ddqthDRef = N(ABBar)*N(JmBar)*ddqthD();

  ddqBoptRef = ddqLBRef + ddqmRef + ddqthDRef;

  return ddqBoptRef;
}
