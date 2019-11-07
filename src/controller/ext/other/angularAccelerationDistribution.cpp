/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::angularAccelerationDistribution(RlsDynamics *io, bool partialBase)
{
  if(debug) DEBUG;

  Vector6d cal_dVCRef;
  cal_dVCRef <<
    io->fb.dvCfb,
    dwCRef;

  MatrixXd En = MatrixXd::Identity(io->info.model.dof.joint, io->info.model.dof.joint);
  MatrixXd E6 = MatrixXd::Identity(6,6);
  

  int rows = io->constraintModel.info.constraint.c.all + io->constraintModel.info.constraint.m.all;
  MatrixXd INV = MatrixXd::Zero(rows, io->info.model.dof.joint);
  MatrixXd MAP = MatrixXd::Zero(rows,6);
  VectorXd ACC = VectorXd::Zero(rows);
  VectorXd NL = VectorXd::Zero(rows);

  INV <<
    io->constraintModel.cal_JcM,
    io->constraintModel.cal_JmM;
  
  MAP <<
    io->constraintModel.mbb_CcM.transpose(),
    io->constraintModel.mbb_CmM.transpose();

  ACC <<
    VectorXd::Zero(io->constraintModel.info.constraint.c.all),
    io->constraintModel.Bm.transpose()*io->fb.cal_dVfb;

  NL <<
    io->constraintModel.cal_dJcM*io->model->dth + io->constraintModel.mbb_dCcM.transpose()*io->model->cal_VM,
    io->constraintModel.cal_dJmM*io->model->dth + io->constraintModel.mbb_dCmM.transpose()*io->model->cal_VM - io->constraintModel.dBm.transpose()*io->model->cal_V;

  cal_dVMRefBar = (E6 - cal_JthM*pInv(INV)*MAP).inverse() * (cal_dVCRef - cal_JthM*(pInv(INV)*(ACC-NL) + N(INV)*jointLimitStop(io, "acc")) - cal_dJthM*io->model->dth);


  // if(partialBase==true){
  //   rootLinkManipulability(io, cal_dVMRefBar, "acc");
  //   io->fb.cal_dVMfb.head(5) = (W*cal_dVMRefBar).head(5) + (dW*io->model->cal_VM).head(5);
  // }
   if(partialBase==true){
    io->fb.cal_dVMfb.head(5) = cal_dVMRefBar.head(5); // for only arm-swing walking
  }
  else{
    io->fb.cal_dVMfb = cal_dVMRefBar;
  }

  io->fb.dwBfb = io->fb.cal_dVMfb.tail(3);

  io->relativeAccelerationMixedMap();

 }
