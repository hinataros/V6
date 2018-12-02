/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalEcmpDistribution()
{
  if(debug) DEBUG;

  (this->*internalForceController_ptr)();

  Vector2d recmp = (des.rXDes - des.drXDes/model->wX).head(2);
  MatrixXd Wecmpc = h_weight(recmp);

  cal_FcBarRef =
    pInv(constraintModel.cal_PcM, Wecmpc)*(cal_dLCRef + model->cal_GC)
    + N(constraintModel.cal_PcM)*cal_FcaBarRef;
}
