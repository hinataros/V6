#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::crb(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  tau = MthHat*ddthRef + cthHat - cal_JcHat.transpose()*cal_FcBarRef;
}
