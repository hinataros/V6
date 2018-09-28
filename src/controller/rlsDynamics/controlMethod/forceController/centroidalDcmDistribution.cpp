/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDcmDistribution(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  (this->*internalForceController_ptr)(info);

  MatrixXd WXc = h_weight(rX.head(2));

  cal_FcBarRef = pInv(cal_PcM, WXc)*(cal_dLCRef + cal_GC) + N(cal_PcM)*cal_FcaBarRef;
}
