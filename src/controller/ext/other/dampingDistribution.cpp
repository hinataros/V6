/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::dampingDistribution(RlsDynamics *io)
{
  if(debug) DEBUG;

  double alpha = 1.0;

  double DA = alpha * io->KDlC(0);

  MatrixXd H = MatrixXd::Zero(io->info.model.dof.joint, io->info.model.dof.joint);
  for(int i=0; i<io->info.model.dof.joint; i++)
    H(i,i) = 1- h(i);

  VectorXd dthArm = VectorXd::Zero(io->info.model.dof.joint);
  // VectorXd dthLeg = VectorXd::Zero(io->info.model.dof.joint);

  dthArm.tail(8) = io->model->dth.tail(8);
  // dthLeg.head(12) = io->model->dth.head(12);

  VectorXd ddthArmDamp = VectorXd::Zero(io->info.model.dof.joint);
  // VectorXd ddthLegDamp = VectorXd::Zero(io->info.model.dof.joint);

  ddthArmDamp = - DA * dthArm;
  // ddthLegDamp = - DA * dthLeg;

  Vector3d DdwRef = Jw * ddthArmDamp + dJw*io->model->dth;
  // Vector3d DdwRef = Jw * ddthLegDamp + dJw*io->model->dth;

  io->fb.dwBfb = dwCRef - DdwRef;

  io->fb.cal_dVMfb.tail(3) = io->fb.dwBfb;

  io->relativeAccelerationMixedMap();

 }
