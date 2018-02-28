/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::staticControl(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // if(info.sim.state)
  tau = gth - cal_Jc.transpose()*cal_FcBarRef;

  // tau = Nast(cal_Jc, Mth)*Mth*ddthD(config, model) + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = Nast(cal_JcM, Mth)*MthC*ddthD(config, model) + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;
  // tau = MthC*ddthD(config, model) + cthC + gth - cal_Jc.transpose()*cal_FcBarRef;
}
