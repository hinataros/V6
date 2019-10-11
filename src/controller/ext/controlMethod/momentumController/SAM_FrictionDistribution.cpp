/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::SAM_FrictionDistribution(RlsDynamics *io)
{
  if(debug) DEBUG;


  VectorXd dlCDes = VectorXd::Zero(3);
  static VectorXd lCDes = VectorXd::Zero(3);

  VectorXd cal_dVMa = VectorXd::Zero(6);
  cal_dVMa <<
    io->fb.dvCfb,
    io->fb.dwBfb;

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

  io->dlCRef = io->model->IC*((E6 - cal_JthM*pInv(INV)*MAP)*cal_dVMa + cal_JthM*(pInv(INV)*(ACC-NL) + N(INV)*jointLimitStop(io, "acc"))).tail(3) + io->model->dIC*wC;

  // double threshold = 0.9;
  
  // for(int i=0; i<3; i++){
  //   if(io->dlCRef(i) > threshold)
  //     io->dlCRef(i) = threshold;
  //   if(io->dlCRef(i) < -threshold)
  //     io->dlCRef(i) = -threshold;
  // }

  systemAngularMomentumLimitation(io);

}
