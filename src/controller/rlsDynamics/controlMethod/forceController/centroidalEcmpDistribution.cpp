/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalEcmpDistribution(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  (this->*internalForceController_ptr)(info);

  Vector2d recmp = (rX - drXDes/wX).head(2);
  MatrixXd Wecmpc = h_weight(recmp);

  cal_FcBarRef = pInv(cal_PcM, Wecmpc)*(cal_dLCRef + cal_GC) + N(cal_PcM)*cal_FcaBarRef;
}
