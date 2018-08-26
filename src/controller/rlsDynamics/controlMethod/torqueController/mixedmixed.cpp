/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::mixedmixed(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  MatrixXd MthHatBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  MthHatBar <<
    HMth.transpose(), MthC;

  tau = MthHatBar*ddqMRef + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;
}
