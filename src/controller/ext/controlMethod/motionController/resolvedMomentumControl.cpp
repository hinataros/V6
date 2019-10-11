/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

VectorXd RLS::Ext::resolvedMomentumControl(RlsDynamics *io)
{
  if(debug) DEBUG;

  int controlDoF = 6;
  MatrixXd S = MatrixXd::Identity(controlDoF,6);
  VectorXd dthF = io->model->dth.head(12);
  VectorXd dthFree = io->model->dth.tail(io->info.model.dof.joint-12);
  MatrixXd HBthF = io->model->HBth.block(0,0,6,12);
  MatrixXd HBthFree = io->model->HBth.block(0,12,6,io->info.model.dof.joint - 12);
  VectorXd cal_VFRef = io->fb.cal_Vfb.head(12);
  MatrixXd cal_JF = io->model->cal_J.block(0,0,12,12);
  MatrixXd HBthFStar = HBthF * cal_JF.inverse();
  MatrixXd HBthStar = io->model->MB - HBthFStar * io->model->bb_TB2k.block(0,0,12,6);

  MatrixXd A = MatrixXd::Zero(controlDoF,6+io->info.model.dof.joint-12);
  VectorXd y = VectorXd::Zero(controlDoF);
  VectorXd dq,dqa;
  VectorXd cal_L = VectorXd::Zero(6);

  MatrixXd bb_TC2B = MatrixXd::Zero(6,6);

  bb_TC2B <<
    Matrix3d::Identity(), -cross(io->model->rB - io->model->rC),
    Matrix3d::Zero(), Matrix3d::Identity();

  MatrixXd cal_JB2C = MatrixXd::Zero(6,io->info.model.dof.joint);

  cal_JB2C.block(0,0,3,io->info.model.dof.joint) = io->model->JB2C;
  
  // S <<
  //   1,0,0,0,0,0,
  //   0,1,0,0,0,0,
  //   0,0,1,0,0,0,
  //   0,0,0,0,0,1;
  
  // cal_L<<
  //   MB(0,0) * vCRef,
  //   IC * wBRef;

  cal_L.head(3) = io->model->M * io->fb.vCfb;

  // cal_L.tail(3) = io->model->IC * io->fb.wBfb;
  cal_L.tail(3) = VectorXd::Zero(3);

  dq = dqa = VectorXd::Zero(io->info.model.dof.all-12);

  io->fb.cal_VBfb = bb_TC2B * io->fb.cal_VMfb - cal_JB2C*io->model->dth;

  A << S*HBthStar, S*HBthFree;
  y = S*(cal_L - HBthFStar*cal_VFRef);
  // dqa << cal_VBRef, dthaRef.tail(info.dof.joint-12);
  dqa << io->fb.cal_VBfb, VectorXd::Zero(io->info.model.dof.joint-12);

  dq = pInv(A)*y + N(A)*dqa;

  io->dthRef <<
    cal_JF.inverse()*(cal_VFRef-io->model->bb_TB2k.block(0,0,12,6)*dq.head(6)),
    dq.tail(io->info.model.dof.joint-12);

  io->dqMRef <<
    dq.head(6),
    io->dthRef;

  return io->dqMRef;
}
