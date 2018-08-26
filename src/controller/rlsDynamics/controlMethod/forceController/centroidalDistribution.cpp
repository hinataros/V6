/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDistribution(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  cal_FcBarRef = pInv(cal_PcM)*(cal_dLCRef + cal_GC);
  // cal_FcBarRef = cal_PcM.inverse()*(cal_dLCRef + cal_GC);
}
