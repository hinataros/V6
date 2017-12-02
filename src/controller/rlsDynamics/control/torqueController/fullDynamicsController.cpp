#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::fullDynamicsController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // acceleration control
  (this->*mc_ptr)(config, info, model);

  // momentum control
  momentumController(config, info, model);

  // force control
  forceController(config, info, model);

  // torque control
  // MatrixXd MthBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  // MthBar <<
  //   model.all.M.block(0,6,6,info.dof.joint).transpose(), Mth;

  // tau = MthBar*ddqRef + cth + gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = HBth.transpose()*dqRef.head(6) + Mth*ddqRef.segment(6,info.dof.joint) + cth + gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = gth - cal_Jc.transpose()*cal_FcBarRef + Nast(cal_Jc, Mth)*Mth*ddthD(config,model);

  MatrixXd MthHatBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  MthHatBar <<
    model.all.MM.block(0,6,6,info.dof.joint).transpose(), MthC;

  // tau = MthHatBar*ddqRef + cthC - cal_JcM.transpose()*cal_FcMBarRef;
  tau = MthHatBar*ddqRef + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = HC.transpose()*dwBRef + MthC*ddthRef + cthC - cal_JcM.transpose()*cal_FcMBarRef;

  // tau = - cal_JcM.transpose()*cal_FcMBarRef;
  // tau = - cal_JcM.transpose()*cal_FcMBarRef + Nast(cal_JcM, Mth)*Mth*ddthD(config,model);
  // tau = - cal_JcM.transpose()*cal_FcMBarRef + Mth*ddthD(config,model);
  // tau = - cal_JcM.transpose()*cal_FcMBarRef + Mth*N(cal_JcM)*ddthD(config,model);

  return tau;
}
