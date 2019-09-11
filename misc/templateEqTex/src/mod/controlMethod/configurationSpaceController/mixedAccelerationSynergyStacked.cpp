/**
   @author Akinori Miyata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedAccelerationSynergyStacked()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  MatrixXd JMBar = MatrixXd::Zero(info.constraint->m.all+info.constraint->c.all, info.model.dof.joint);
  JMBar <<
    constraintModel.cal_JmM,
    constraintModel.cal_JcM;

  VectorXd VMBar = VectorXd::Zero(info.constraint->m.all+info.constraint->c.all);
  VMBar <<
    cal_dVmBarRef,
    VectorXd::Zero(info.constraint->c.all);

  MatrixXd PMBar = MatrixXd::Zero(info.constraint->m.all+info.constraint->c.all, 6);
  PMBar <<
    constraintModel.mbb_CmM.transpose(),
    constraintModel.mbb_CcM.transpose();

  MatrixXd dJMBar = MatrixXd::Zero(info.constraint->m.all+info.constraint->c.all, info.model.dof.all);
  dJMBar <<
    constraintModel.cal_dPmM.transpose(), constraintModel.cal_dJmM,
    constraintModel.cal_dPcM.transpose(), constraintModel.cal_dJcM;

  ddthRef = pInv(JMBar) * (VMBar - PMBar * fb.cal_dVMfb - dJMBar * model->dqM) + N(JMBar) * ddthD();

  ddqMoptRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMoptRef;
}
