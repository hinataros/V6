/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedBaseAngularDecomposedMomentum()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  MatrixXd AMBar = MatrixXd::Zero(wBcD+pcD+lCcD+info.constraint->m.all+info.constraint->c.all, info.model.dof.all);
  MatrixXd bb = MatrixXd::Zero(3, info.model.dof.all);
  bb.block(0,3, 3,3) = MatrixXd::Identity(3,3);
  AMBar <<
    BwB.transpose() * bb,
    BLC.transpose() * model->cal_AM,
    constraintModel.JmM,
    constraintModel.JcM;

  VectorXd VMBar = VectorXd::Zero(3+6+info.constraint->m.all+info.constraint->c.all);
  VMBar <<
    fb.dwBfb,
    cal_dLCRef,
    cal_dVmBarRef,
    VectorXd::Zero(info.constraint->c.all);

  MatrixXd Bin = MatrixXd::Zero(wBcD+pcD+lCcD+info.constraint->m.all+info.constraint->c.all, 3+6+info.constraint->m.all+info.constraint->c.all);
  Bin <<
    BwB.transpose(), MatrixXd::Zero(wBcD, 6+info.constraint->m.all+info.constraint->c.all),
    MatrixXd::Zero(pcD+lCcD,3), BLC.transpose(), MatrixXd::Zero(pcD+lCcD, info.constraint->m.all+info.constraint->c.all),
    MatrixXd::Zero(info.constraint->m.all+info.constraint->c.all, 3+6), MatrixXd::Identity(info.constraint->m.all+info.constraint->c.all, info.constraint->m.all+info.constraint->c.all);

  MatrixXd dAMBar = MatrixXd::Zero(wBcD+pcD+lCcD+info.constraint->m.all+info.constraint->c.all, info.model.dof.all);
  dAMBar <<
    MatrixXd::Zero(wBcD,info.model.dof.all),
    BLC.transpose() * model->cal_dAM,
    constraintModel.dJmM,
    constraintModel.dJcM;

  // ddqMoptRef = pInv(AMBar) * (Bin*VMBar - dAMBar * model->dqM) + N(AMBar) * ddqthinit();
  ddqMoptRef = pInv(AMBar) * (Bin*VMBar - dAMBar * model->dqM) + N(AMBar) * ddqthD();

//////////
  ddthRef = ddqMoptRef.segment(6, info.model.dof.joint);

  VectorXd cal_dLCBarOpt = model->cal_AM*ddqMoptRef + model->cal_dAM*model->dqM;
  cal_dLCRef = BLC*BLC.transpose()*cal_dLCRef + BLCAut*BLCAut.transpose()*cal_dLCBarOpt;
//////////


  return ddqMoptRef;
}
