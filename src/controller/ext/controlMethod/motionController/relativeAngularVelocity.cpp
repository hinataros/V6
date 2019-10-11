/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

VectorXd RLS::Ext::relativeAngularVelocity(RlsDynamics *io)
{
  if(debug) DEBUG;

  wCRef = VectorXd::Zero(3);

  angularVelocityDistribution(io, true);

  DwRef = wCRef - io->fb.wBfb;

  // constraint
  VectorXd dthcRef = pInv(io->constraintModel.cal_JcM)*io->cal_VcMBarRef;

  // mobility
  MatrixXd cal_JmMBar = io->constraintModel.cal_JmM*N(io->constraintModel.cal_JcM);
  VectorXd cal_VmMTildeRef = io->cal_VmMBarRef - io->constraintModel.cal_JmM*dthcRef;

  VectorXd dthmRef = pInv(cal_JmMBar)*cal_VmMTildeRef;

  // relative angular momentum
  MatrixXd NN = N(io->constraintModel.cal_JcM)*N(cal_JmMBar);
  MatrixXd JwBar = Jw * NN;

  VectorXd wTilde = Jw*(dthcRef + dthmRef);
  VectorXd dthwRef = pInv(JwBar)*(DwRef - wTilde);

  // null space
  VectorXd dthnRef = NN*N(JwBar)*jointLimitAvoidance(io, "vel");

  // io->dthRef = dthcRef + dthmRef + dthwRef;
  io->dthRef = dthcRef + dthmRef + dthwRef + dthnRef;

  io->dqMRef <<
    io->fb.cal_VMfb,
    io->dthRef;

  VectorXd dqcRef = VectorXd::Zero(io->info.model.dof.all);
  dqcRef <<
    io->constraintModel.bb_ScB.topLeftCorner(3,3)*(io->fb.vCfb + cross(io->model->rB2C)*io->fb.wBfb - io->model->JB2C*io->dthRef),
    io->constraintModel.bb_ScB.bottomRightCorner(3,3)*io->fb.wBfb,
    io->dthRef;

  return dqcRef;

}
