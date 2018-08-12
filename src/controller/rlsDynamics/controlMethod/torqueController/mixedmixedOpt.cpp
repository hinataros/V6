/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mixedmixedOpt(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd MthHatBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  MthHatBar <<
    HMth.transpose(), MthC;

  tau = MthHatBar*ddqMoptRef + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;

  // MatrixXd A = MatrixXd::Zero(info.dof.joint, 3+info.dof.joint);
  // A <<
  //   HC.transpose(), MthC;

  // tau = A*ddqwoptRef + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = HMth.transpose()*cal_dVMRef + MthC*ddthRef + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;
}
