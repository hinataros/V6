#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseDistribution(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_FcBarRef = pInv(cal_Pc)*(cal_dLBRef + cal_GB);
}
