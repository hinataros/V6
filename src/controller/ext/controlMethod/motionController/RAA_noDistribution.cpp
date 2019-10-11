/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

VectorXd RLS::Ext::RAA_noDistribution(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->relativeAccelerationMixedMap();

  dwCRef = io->model->IC.inverse() * (io->dlCRef - io->model->dIC*wC);

  dDwRef = (dwCRef - io->fb.dwBfb);


  int rows = io->constraintModel.info.constraint.c.all + io->constraintModel.info.constraint.m.all + 3;
  MatrixXd INV = MatrixXd::Zero(rows, io->info.model.dof.joint);
  MatrixXd MAP = MatrixXd::Zero(rows,6);
  VectorXd ACC = VectorXd::Zero(rows);
  VectorXd NL = VectorXd::Zero(rows);

  INV <<
    io->constraintModel.cal_JcM,
    io->constraintModel.cal_JmM,
    Jw;

  MAP <<
    io->constraintModel.mbb_CcM.transpose(),
    io->constraintModel.mbb_CmM.transpose(),
    MatrixXd::Zero(3,6);

  ACC <<
    VectorXd::Zero(io->constraintModel.info.constraint.c.all),
    io->constraintModel.Bm.transpose()*io->fb.cal_dVfb,
    dDwRef;

  NL <<
    io->constraintModel.cal_dJcM*io->model->dth + io->constraintModel.mbb_dCcM.transpose()*io->model->cal_VM,
    io->constraintModel.cal_dJmM*io->model->dth + io->constraintModel.mbb_dCmM.transpose()*io->model->cal_VM - io->constraintModel.dBm.transpose()*io->model->cal_V,
    dJw*io->model->dth;
    

  io->ddthRef = pInv(INV)*(ACC - MAP*io->fb.cal_dVMfb - NL) + N(INV)*jointLimitStop(io, "acc");

  ///////////////////////////////////////////////////////////////////////////////////////////
  
  io->ddqMRef <<
    io->fb.cal_dVMfb,
    io->ddthRef;

  return io->ddqMRef;

}
