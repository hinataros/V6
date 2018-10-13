/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::baseVelocitySynergy()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  // constraint
  VectorXd dthcRef = pInv(cal_Jc)*cal_VcBBarRef;

  // mobility
  MatrixXd cal_JmBar = cal_Jm*N(cal_Jc);
  VectorXd cal_VmTildeRef = cal_VmBBarRef - cal_Jm*dthcRef;

  VectorXd dthmRef = pInv(cal_JmBar)*cal_VmTildeRef;

  dthRef = dthcRef + dthmRef;

  dqBRef <<
    fb.cal_VBfb,
    dthRef;

  VectorXd dqcRef = VectorXd::Zero(info.model.dof.all);
  dqcRef <<
    bb_ScB*fb.cal_VBfb,
    dthRef;

  return dqcRef;
}
