/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedVelocitySynergy()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  // constraint
  VectorXd dthcRef = pInv(cal_JcM)*cal_VcMBarRef;

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);
  VectorXd cal_VmMTildeRef = cal_VmMBarRef - cal_JmM*dthcRef;

  VectorXd dthmRef = pInv(cal_JmMBar)*cal_VmMTildeRef;

  // VectorXd dthnRef = N(cal_JcM)*N(cal_JmMBar)*dthaRef;

  dthRef = dthcRef + dthmRef;

  dqMRef <<
    fb.cal_VMfb,
    dthRef;

  VectorXd dqcRef = VectorXd::Zero(info.model.dof.all);
  dqcRef <<
    bb_ScB.topLeftCorner(3,3)*(fb.vCfb + cross(model->rB2C)*fb.wBfb - model->JB2C*dthRef),
    bb_ScB.bottomRightCorner(3,3)*fb.wBfb,
    dthRef;

  return dqcRef;
}
