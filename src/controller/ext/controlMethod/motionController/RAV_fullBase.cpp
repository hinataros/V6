/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

VectorXd RLS::Ext::RAV_fullBase(RlsDynamics *io)
{
  if(debug) DEBUG;

  wCRef = VectorXd::Zero(3);

  angularVelocityDistribution(io, false);

  DwRef = wCRef - io->fb.wBfb;


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
