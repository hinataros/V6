/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::staticControl(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // if(info.sim.state)
  // tau = gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = Nast(cal_Jc, Mth)*Mth*ddthD(config, model) + gth - cal_Jc.transpose()*cal_FcBarRef;
  tau = Nast(cal_JcM, Mth)*MthC*ddthD(info) + gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = MthC*ddthD(config, model) + gth - cal_Jc.transpose()*cal_FcBarRef;
}
