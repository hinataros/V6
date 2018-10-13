/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDcmDistribution()
{
  if(debug) DEBUG;

  (this->*internalForceController_ptr)();

  MatrixXd WX = h_weight(model->rX.head(2));

  cal_FcBarRef = pInv(cal_PcM, WX)*(cal_dLCRef + model->cal_GC) + N(cal_PcM)*cal_FcaBarRef;
}
