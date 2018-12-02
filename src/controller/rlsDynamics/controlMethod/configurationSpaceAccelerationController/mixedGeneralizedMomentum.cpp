/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedGeneralizedMomentum()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  MatrixXd ACBar = MatrixXd::Zero(6+info.constraint->c.all, info.model.dof.all);
  ACBar <<
    model->cal_AM,
    constraintModel.JcM;

  MatrixXd dACBar = MatrixXd::Zero(6+info.constraint->c.all, info.model.dof.all);
  dACBar <<
    model->cal_dAM,
    constraintModel.dJcM;

  VectorXd cal_dLCBarRef = VectorXd::Zero(6+info.constraint->c.all);
  cal_dLCBarRef.head(6) = cal_dLCRef;

  VectorXd ddqLCRef = pInv(ACBar)*(cal_dLCBarRef - dACBar*model->dqM);

  MatrixXd JmMBar = constraintModel.JmM*N(ACBar);

  VectorXd dVmBarRef = cal_dVmBarRef + constraintModel.dBm.transpose()*model->cal_V;
  VectorXd dVmTildeRef = dVmBarRef - constraintModel.dJmM*model->dqM - constraintModel.JmM*ddqLCRef;

  VectorXd ddqmRef = N(ACBar)*pInv(JmMBar)*dVmTildeRef;

  // ddqMoptRef = ddqLCRef + ddqmRef + N(ACBar)*N(JmMBar)*ddqthD();
  ddqMoptRef = ddqLCRef + ddqmRef + N(ACBar)*N(JmMBar)*ddqthinit();

  return ddqMoptRef;
}
