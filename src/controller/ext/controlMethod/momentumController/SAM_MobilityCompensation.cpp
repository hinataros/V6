/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::SAM_MobilityCompensation(RlsDynamics *io)
{
  if(debug) DEBUG;

  VectorXd dlCDes = VectorXd::Zero(3);
  static VectorXd lCDes = VectorXd::Zero(3);

  VectorXd cal_dVCwB0 = VectorXd::Zero(6);
  cal_dVCwB0 <<
    io->fb.dvCfb,
    - io->KDlC * io->model->wB;

  MatrixXd En = MatrixXd::Identity(io->info.model.dof.joint, io->info.model.dof.joint);
  MatrixXd E6 = MatrixXd::Identity(6,6);

  MatrixXd cal_JmMBar = io->constraintModel.cal_JmM*N(io->constraintModel.cal_JcM);
  MatrixXd cal_dJmMBar = io->constraintModel.cal_dJmM*N(io->constraintModel.cal_JcM) + io->constraintModel.cal_JmM*dN(io->constraintModel.cal_JcM,io->constraintModel.cal_dJcM);

  // nonlinear
  VectorXd hcM =
    io->constraintModel.mbb_dCcM.transpose()*io->model->cal_VM
    + io->constraintModel.cal_dJcM*io->model->dth;

  VectorXd hmM =
    -io->constraintModel.dBm.transpose()*io->model->cal_V
    + io->constraintModel.mbb_dCmM.transpose()*io->model->cal_VM
    + io->constraintModel.cal_dJmM*io->model->dth;

  VectorXd h =
    pInv(io->constraintModel.cal_JcM)*hcM
    + pInv(cal_JmMBar)*(hmM - io->constraintModel.cal_JmM*pInv(io->constraintModel.cal_JcM)*hcM);

  VectorXd ddth_other = pInv(cal_JmMBar)*io->constraintModel.Bm.transpose()*io->fb.cal_dVfb - h + N(io->constraintModel.cal_JcM)*N(cal_JmMBar)*jointLimitStop(io, "acc");

  MatrixXd P = pInv(cal_JmMBar)*io->constraintModel.mbb_CmM.transpose() + (En - pInv(cal_JmMBar)*io->constraintModel.cal_JmM)*pInv(io->constraintModel.cal_JcM)*io->constraintModel.mbb_CcM.transpose();

  io->dlCRef = (io->model->MC*(E6 - cal_JthM*P)*cal_dVCwB0).tail(3) + io->model->HC * ddth_other + io->model->IC*dJw*io->model->dth + io->model->dIC*wC;

}
