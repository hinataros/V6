#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::base(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd MthBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  MthBar <<
    model.hoap2.all.M.block(0,6,6,info.dof.joint).transpose(), Mth;

  tau = MthBar*ddqRef + cth + gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = gth - cal_Jc.transpose()*cal_FcBarRef
  //   + Nast(cal_Jc, Mth)*Mth*ddthD(config,model);
}
