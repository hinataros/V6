/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

VectorXd RLS::Ext::RAV_noDistribution(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->relativeVelocityMixedMap();

  wCRef = VectorXd::Zero(3);

  DwRef = wCRef - io->fb.wBfb;

  // ////////////////////// restricted /////////////////////////////////
  
  // // constraint
  // VectorXd dthcRef = pInv(io->constraintModel.cal_JcM)*io->cal_VcMBarRef;

  // // mobility
  // MatrixXd cal_JmMBar = io->constraintModel.cal_JmM*N(io->constraintModel.cal_JcM);
  // VectorXd cal_VmMTildeRef = io->cal_VmMBarRef - io->constraintModel.cal_JmM*dthcRef;

  // VectorXd dthmRef = pInv(cal_JmMBar)*cal_VmMTildeRef;

  // // relative angular momentum
  // MatrixXd NN = N(io->constraintModel.cal_JcM)*N(cal_JmMBar);
  // MatrixXd JwBar = Jw * NN;

  // VectorXd wTilde = Jw*(dthcRef + dthmRef);
  // VectorXd dthwRef = pInv(JwBar)*(DwRef - wTilde);

  // // null space
  // VectorXd dthnRef = NN*N(JwBar)*jointLimitAvoidance(io, "vel");
  // // VectorXd dthnRef = NN*N(JwBar)*VectorXd::Zero(io->info.model.dof.joint);

  // // io->dthRef = dthcRef + dthmRef + dthwRef;
  // io->dthRef = dthcRef + dthmRef + dthwRef + dthnRef;

  //////////////////////// stack /////////////////////////////////

  int rows = io->constraintModel.info.constraint.c.all+io->constraintModel.info.constraint.m.all+3;
  MatrixXd INV = MatrixXd::Zero(rows,io->info.model.dof.joint);
  MatrixXd MAP = MatrixXd::Zero(rows,6);
  VectorXd VEL = VectorXd::Zero(rows);
  MatrixXd En = MatrixXd::Identity(io->info.model.dof.joint, io->info.model.dof.joint);
  MatrixXd E6 = MatrixXd::Identity(6,6);

  INV <<
    io->constraintModel.cal_JcM,
    io->constraintModel.cal_JmM,
    Jw;

  MAP <<
    io->constraintModel.mbb_CcM.transpose(),
    io->constraintModel.mbb_CmM.transpose(),
    MatrixXd::Zero(3,6);

  VEL <<
    VectorXd::Zero(io->constraintModel.info.constraint.c.all),
    io->constraintModel.Bm.transpose()*io->fb.cal_Vfb,
    DwRef;

  io->dthRef = pInv(INV)*(VEL - MAP*io->fb.cal_VMfb) + N(INV)*jointLimitStop(io, "vel");

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
