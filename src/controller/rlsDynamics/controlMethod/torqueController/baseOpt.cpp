/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseOpt(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd MthBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  MthBar <<
    HBth.transpose(), Mth;

  tau = MthBar*ddqBoptRef + cth + gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = gth - cal_Jc.transpose()*cal_FcBarRef
  //   + Nast(cal_Jc, Mth)*Mth*ddthD(config,model);
}