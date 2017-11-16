#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::forceController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_FcBarRef = pInv(cal_Pc)*(cal_dLBRef + cal_GB);

  cal_FcMBarRef = pInv(cal_PcM)*(cal_dLCRef + cal_GC);

  // o(cal_Pc);
  // o(cal_PcM);
}
