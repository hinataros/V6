/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDistribution()
{
  if(debug) DEBUG;

  cal_FcBarRef = pInv(constraintModel.mbb_CcM)*(cal_dLCRef + model->cal_GC);
  // cal_FcBarRef = constraintModel.mbb_CcM.inverse()*(cal_dLCRef + model->cal_GC);
}
