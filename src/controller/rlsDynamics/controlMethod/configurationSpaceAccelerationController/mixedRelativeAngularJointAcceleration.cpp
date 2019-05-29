/**
   @author Akinori Miyata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedRelativeAngularJointAcceleration()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  MatrixXd Jw = model->IC.inverse() * model->HC;
  MatrixXd dICinv = -model->IC.inverse()*model->dIC*model->IC.inverse();
  MatrixXd dJw = dICinv * model->HC + model->IC.inverse() * model->dHC;

  MatrixXd JMBar = MatrixXd::Zero(wBcD+info.constraint->m.all+info.constraint->c.all, info.model.dof.joint);
  JMBar <<
    BwB.transpose()*Jw,
    // model->cal_AM,
    constraintModel.cal_JmM,
    constraintModel.cal_JcM;
  Vector3d deltaw;
  Vector3d dwC = model->IC.inverse() * (cal_dLCRef.segment(3,3) - model->dIC*(model->wB + Jw*model->dth));
  deltaw = dwC - fb.dwBfb;

  VectorXd VMBar = VectorXd::Zero(wBcD+info.constraint->m.all+info.constraint->c.all);
  VMBar <<
    BwB.transpose()*deltaw,
    // cal_dLCRef,
    cal_dVmBarRef,
    VectorXd::Zero(info.constraint->c.all);
    // cal_dVmMBarRef;

  MatrixXd PBar = MatrixXd::Zero(wBcD+info.constraint->m.all+info.constraint->c.all, 6);
  PBar <<
    MatrixXd::Zero(wBcD,3), BwB.transpose()*MatrixXd::Identity(3,3),
    constraintModel.cal_PmM.transpose(),
    constraintModel.cal_PcM.transpose();

  MatrixXd dJMBar = MatrixXd::Zero(wBcD+info.constraint->m.all+info.constraint->c.all, info.model.dof.all);
  dJMBar <<
    MatrixXd::Zero(wBcD,6), BwB.transpose()*dJw,
    // BLC.transpose() * model->cal_dAM,
    constraintModel.cal_dPmM.transpose(), constraintModel.cal_dJmM,
    constraintModel.cal_dPcM.transpose(), constraintModel.cal_dJcM;

  // ddqMoptRef = pInv(AMBar) * (Bin*VMBar - dJMBar * model->dqM) + N(AMBar) * ddqthinit();
  ddthRef = pInv(JMBar) * (VMBar - PBar * fb.cal_dVMfb - dJMBar * model->dqM) + N(JMBar) * ddthD();
  // o(N(AMBar) * ddqthinit();

  ddqMoptRef <<
    fb.cal_dVMfb,
    ddthRef;

  return ddqMoptRef;
}
