/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::angularVelocityDistribution(RlsDynamics *io, bool partialBase)
{
  if(debug) DEBUG;

  Vector6d cal_VCRef;
  cal_VCRef <<
    io->fb.vCfb,
    wCRef;


  /////////////////////////////// stack ////////////////////////////

  int rows = io->constraintModel.info.constraint.c.all+io->constraintModel.info.constraint.m.all;
  MatrixXd INV = MatrixXd::Zero(rows,io->info.model.dof.joint);
  MatrixXd MAP = MatrixXd::Zero(rows,6);
  VectorXd VEL = VectorXd::Zero(rows);
  MatrixXd En = MatrixXd::Identity(io->info.model.dof.joint, io->info.model.dof.joint);
  MatrixXd E6 = MatrixXd::Identity(6,6);

  INV <<
    io->constraintModel.cal_JcM,
    io->constraintModel.cal_JmM;

  MAP <<
    io->constraintModel.mbb_CcM.transpose(),
    io->constraintModel.mbb_CmM.transpose();

  VEL <<
    VectorXd::Zero(io->constraintModel.info.constraint.c.all),
    io->constraintModel.Bm.transpose()*io->fb.cal_Vfb;

  cal_VMRefBar = (E6 - cal_JthM*pInv(INV)*MAP).inverse() * (cal_VCRef - cal_JthM*(pInv(INV)*VEL + N(INV)*jointLimitStop(io, "vel")));
  
 
  if(partialBase==true){
    io->fb.cal_VMfb.head(5) = cal_VMRefBar.head(5);
  }
  else{
    io->fb.cal_VMfb = cal_VMRefBar;
  }

  io->fb.wBfb = io->fb.cal_VMfb.tail(3);

  io->relativeVelocityMixedMap();

}
