/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rcamd()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  // 1st
  // ****************************************************************
  VectorXd ddqcRef = pInv(constraintModel.JcM)*(-constraintModel.dJcM*model->dqM);

  // // // 2nd
  // // // ****************************************************************
  // MatrixXd cal_ApwB = MatrixXd::Zero(3+3,info.model.dof.all);
  // cal_ApwB.block(0,0,3,info.model.dof.all) = model->cal_AM.block(0,0,3,info.model.dof.all);
  // cal_ApwB.block(3,3,3,3) = Matrix3d::Identity();

  // MatrixXd cal_AMBar = cal_ApwB*N(JcM);
  // VectorXd cal_dLCBarRef = VectorXd::Zero(3+3);
  // cal_dLCBarRef <<
  //   (cal_dLCRef - model->cal_dAM*model->dqM).head(3),
  //   fb.dwBfb;
  // VectorXd ddqlRef = pInv(cal_AMBar)*(cal_dLCBarRef - cal_ApwB*ddqcRef);

  // // // 2nd
  // // // ****************************************************************
  // MatrixXd cal_AMwB = MatrixXd::Zero(3+6,info.model.dof.all);
  // cal_AMwB.block(0,3,3,3) = Matrix3d::Identity();
  // cal_AMwB.block(3,0,6,info.model.dof.all) = model->cal_AM;

  // MatrixXd cal_AMBar = cal_AMwB*N(JcM);
  // VectorXd cal_dLCBarRef = VectorXd::Zero(3+6);
  // cal_dLCBarRef <<
  //   fb.dwBfb,
  //   cal_dLCRef - model->cal_dAM*model->dqM;
  // VectorXd ddqlRef = pInv(cal_AMBar)*(cal_dLCBarRef - cal_AMwB*ddqcRef);

  // 2nd
  // ****************************************************************
  MatrixXd cal_AMBar = model->cal_AM*N(constraintModel.JcM);
  Vector6d cal_dLCBarRef = cal_dLCRef - model->cal_dAM*model->dqM;
  VectorXd ddqlRef = pInv(cal_AMBar)*(cal_dLCBarRef - model->cal_AM*ddqcRef);

  // 3rd
  // ****************************************************************
  MatrixXd JmMBar = constraintModel.JmM*N(constraintModel.JcM)*N(cal_AMBar);
  VectorXd cal_dVmTildeRef = cal_dVmBarRef - constraintModel.dJmM*model->dqM;
  VectorXd ddqmRef = pInv(JmMBar)*(cal_dVmTildeRef - constraintModel.JmM*(ddqcRef + ddqlRef));

  // 4th
  // ****************************************************************
  VectorXd ddqnRef = N(constraintModel.JcM)*N(cal_AMBar)*N(JmMBar)*ddqthinit();

  // ****************************************************************
  ddqMoptRef = ddqcRef + ddqlRef + ddqmRef + ddqnRef;

  return ddqMoptRef;
}
