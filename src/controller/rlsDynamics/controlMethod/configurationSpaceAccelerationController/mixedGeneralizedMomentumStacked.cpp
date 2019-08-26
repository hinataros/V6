/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedGeneralizedMomentumStacked()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  MatrixXd AMBar = MatrixXd::Zero(6+info.constraint->m.all+info.constraint->c.all, info.model.dof.all);
  AMBar <<
    model->cal_AM,
    constraintModel.JmM,
    constraintModel.JcM;

  VectorXd VMBar = VectorXd::Zero(6+info.constraint->m.all+info.constraint->c.all);
  VMBar <<
    cal_dLCRef,
    cal_dVmBarRef,
    cal_dVcBarRef;

  MatrixXd dAMBar = MatrixXd::Zero(6+info.constraint->m.all+info.constraint->c.all, info.model.dof.all);
  dAMBar <<
    model->cal_dAM,
    constraintModel.dJmM,
    constraintModel.dJcM;

  // ddqMoptRef = pInv(AMBar) * (Bin*VMBar - dAMBar * model->dqM) + N(AMBar) * ddqthinit();
  ddqMoptRef = pInv(AMBar) * (VMBar - dAMBar * model->dqM) + N(AMBar) * ddqthinit();

  return ddqMoptRef;
}
