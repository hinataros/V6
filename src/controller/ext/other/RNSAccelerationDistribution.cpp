/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::RNSAccelerationDistribution(RlsDynamics *io)
{
  if(debug) DEBUG;

  ///////////////////////////////////// stack //////////////////////////////////

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

  MatrixXd pInvMap;
  pInvMap = (MAP.transpose()*MAP).inverse()*MAP.transpose();

  MatrixXd NullMap;
  NullMap = - MatrixXd::Identity(6,6) + MAP.transpose()*pInvMap.transpose();

  VectorXd wBDamper = VectorXd::Zero(6);
  wBDamper <<
    io->fb.dvCfb,
    -1 * io->fb.KdwB*io->model->wB;

  cal_dVMRefBar = pInvMap * (ACC-NL) + NullMap*wBDamper;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  io->fb.cal_dVMfb = cal_dVMRefBar;

  io->fb.dwBfb = io->fb.cal_dVMfb.tail(3);
  
  io->relativeAccelerationMixedMap();

}
