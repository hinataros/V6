#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::torqueController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // tau = HBth.transpose()*cal_dVBRef + Mth*ddthRef + cth + gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = HBth.transpose()*dqRef.head(6) + Mth*ddqRef.segment(6,info.dof.joint) + cth + gth - cal_Jc.transpose()*cal_FcBarRef;
  tau = gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = HC.transpose()*dwBRef + MthC*ddthRef + cthC - cal_JcM.transpose()*cal_FcMBarRef;
  // tau = -cal_JcM.transpose()*cal_FcMBarRef;

  return tau;
}
