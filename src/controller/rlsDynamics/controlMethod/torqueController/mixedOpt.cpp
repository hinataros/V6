/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mixedOpt(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  MatrixXd MthHatBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  MthHatBar <<
    HMth.transpose(), MthC;

  tau = MthHatBar*ddqMoptRef + cthC - cal_JcM.transpose()*cal_FcBarRef;

  // ******************************************************************************
  // tau = - cal_JcM.transpose()*cal_FcBarRef;
  // tau = - cal_JcM.transpose()*cal_FcBarRef
  //   + Nast(cal_JcM, Mth)*Mth*ddthD(config,model);

  // tau = - cal_JcM.transpose()*cal_FcBarRef + Mth*ddthD(config,model);
  // tau = - cal_JcM.transpose()*cal_FcBarRef + Mth*N(cal_JcM)*ddthD(config,model);
}
