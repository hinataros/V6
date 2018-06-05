/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mixed(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd MthHatBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  MthHatBar <<
    model.hoap2.all.MM.block(0,6,6,info.dof.joint).transpose(), MthC;

  tau = MthHatBar*ddqMRef + cthC - cal_JcM.transpose()*cal_FcBarRef;

  // ******************************************************************************
  // tau = - cal_JcM.transpose()*cal_FcBarRef;
  // tau = - cal_JcM.transpose()*cal_FcBarRef
  //   + Nast(cal_JcM, Mth)*Mth*ddthD(config,model);

  // tau = - cal_JcM.transpose()*cal_FcBarRef + Mth*ddthD(config,model);
  // tau = - cal_JcM.transpose()*cal_FcBarRef + Mth*N(cal_JcM)*ddthD(config,model);
}
