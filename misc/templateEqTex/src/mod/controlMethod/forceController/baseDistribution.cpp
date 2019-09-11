/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseDistribution()
{
  if(debug) DEBUG;

  cal_FcBarRef = pInv(constraintModel.mbb_Cc)*(cal_dLBRef + model->cal_GB);
}
