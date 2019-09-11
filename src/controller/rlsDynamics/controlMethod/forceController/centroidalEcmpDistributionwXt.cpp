/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalEcmpDistributionwXt()
{
  if(debug) DEBUG;

  (this->*internalForceController_ptr)();

  Vector2d recmp = (des.rXDes - des.drXDes/model->wXt).head(2);
  MatrixXd Wecmpc = h_weight(recmp);

  cal_FcaBarRef = VectorXd::Zero(info.constraint->c.all);

  cal_FcBarRef =
    pInv(constraintModel.mbb_CcM, Wecmpc)*(cal_dLCRef + model->cal_GC)
    + N(constraintModel.mbb_CcM)*cal_FcaBarRef;
}
