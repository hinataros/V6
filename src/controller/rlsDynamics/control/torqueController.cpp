#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  tau = HBth.transpose()*cal_dVBRef + Mth*ddthRef + cth + gth - cal_Jc.transpose()*cal_FcBarRef;
}
