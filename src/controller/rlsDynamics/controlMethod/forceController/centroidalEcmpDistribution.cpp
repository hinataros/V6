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

  Vector2d recmp = (model->rX - fb.drXfb/model->wX).head(2);
  MatrixXd Wecmpc = h_weight(recmp);
  // MatrixXd Wecmpc = h_weight(recmp, model->r[0].head(2)+distOffset, model->r[1].head(2)-distOffset);

  cal_FcaBarRef = VectorXd::Zero(info.constraint->c.all);

  cal_FcBarRef =
    pInv(constraintModel.cal_PcM, Wecmpc)*(cal_dLCRef + model->cal_GC)
    + N(constraintModel.cal_PcM)*cal_FcaBarRef;
}
