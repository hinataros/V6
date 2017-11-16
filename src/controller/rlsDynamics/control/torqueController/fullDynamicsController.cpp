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
  // tau = HBth.transpose()*cal_dVBRef + Mth*ddthRef + cth + gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = HBth.transpose()*dqRef.head(6) + Mth*ddqRef.segment(6,info.dof.joint) + cth + gth - cal_Jc.transpose()*cal_FcBarRef;
  tau = gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = HC.transpose()*dwBRef + MthC*ddthRef + cthC - cal_JcM.transpose()*cal_FcMBarRef;
  // tau = cthC - cal_JcM.transpose()*cal_FcMBarRef;

  // o(cal_Jc);
  // o(cal_JcM);
  // pause;

  return tau;
}
