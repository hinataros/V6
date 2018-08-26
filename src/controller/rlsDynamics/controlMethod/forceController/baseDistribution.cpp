/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseDistribution(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  cal_FcBarRef = pInv(cal_Pc)*(cal_dLBRef + cal_GB);
}
