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

  MatrixXd MthHatBar = MatrixXd::Zero(info.dof.joint, info.dof.all);
  MthHatBar <<
    model.hoap2.all.MM.block(0,6,6,info.dof.joint).transpose(), MthC;

  tau = MthHatBar*ddqRef + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;
}
