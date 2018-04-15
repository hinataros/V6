/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mixedmixed(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // MatrixXd MthHatBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  // MthHatBar <<
  //   HMth.transpose(), MthC;

  // tau = MthHatBar*ddqRef + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;
  tau = gth - cal_Jc.transpose()*cal_FcBarRef;
}
