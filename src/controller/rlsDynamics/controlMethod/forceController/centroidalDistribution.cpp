/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDistribution(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_FcBarRef = pInv(cal_PcM)*(cal_dLCRef + cal_GC);
}
