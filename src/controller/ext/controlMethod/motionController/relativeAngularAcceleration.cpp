/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

VectorXd RLS::Ext::relativeAngularAcceleration(RlsDynamics *io)
{
  if(debug) DEBUG;

  dwCRef = io->model->IC.inverse() * (io->dlCRef - io->model->dIC*(io->model->wB + Jw*io->model->dth));

  angularAccelerationDistribution(io, true);
  // dampingDistribution(io);

  dDwRef = (dwCRef - io->fb.dwBfb);
  
  // constraint
  VectorXd ddthcRef = pInv(io->constraintModel.cal_JcM)*io->cal_dVcMBarRef;

  // mobility
  MatrixXd cal_JmMBar = io->constraintModel.cal_JmM*N(io->constraintModel.cal_JcM);

  VectorXd cal_dVmMTildeRef = io->cal_dVmMBarRef - io->constraintModel.cal_JmM*ddthcRef;
  VectorXd ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef;

  // relative angular momentum
  MatrixXd NN = N(io->constraintModel.cal_JcM)*N(cal_JmMBar);
  MatrixXd JwBar = Jw * NN;

  VectorXd dwTilde = - Jw*(ddthcRef + ddthmRef);
  // VectorXd ddthwRef = pInv(JwBar, weightJw(config,info,model,Jw,Jw*model.hoap2.all.dth))*(- KDlC*Jw*model.hoap2.all.dth + cal_dVwTildeRef);
  VectorXd ddthwRef = pInv(JwBar)*(dDwRef - dwTilde);

  // nonlinear
  VectorXd hcM =
    io->constraintModel.mbb_dCcM.transpose()*io->model->cal_VM
    + io->constraintModel.cal_dJcM*io->model->dth;

  VectorXd hmM =
    - io->constraintModel.dBm.transpose()*io->model->cal_V
    + io->constraintModel.mbb_dCmM.transpose()*io->model->cal_VM
    + io->constraintModel.cal_dJmM*io->model->dth;
  VectorXd hmMBar =
    hmM - io->constraintModel.cal_JmM*pInv(io->constraintModel.cal_JcM)*hcM;

  VectorXd hw =
    dJw*io->model->dth;
  VectorXd hwBar =
    hw - Jw*(pInv(io->constraintModel.cal_JcM)*hcM + pInv(cal_JmMBar)*hmMBar);

  VectorXd h =
    pInv(io->constraintModel.cal_JcM)*hcM
    + pInv(cal_JmMBar)*hmMBar
    + pInv(JwBar)*hwBar;

  // redanduncy
  VectorXd ddthnRef = NN*N(JwBar)*io->ddthD();
  // VectorXd ddthnRef = NN*N(JwBar)*jointLimitAvoidance(io, "acc");

  
  io->ddthRef = ddthcRef + ddthmRef + ddthwRef - h + ddthnRef;
  
  io->ddqMRef <<
    io->fb.cal_dVMfb,
    io->ddthRef;

  return io->ddqMRef;
}
