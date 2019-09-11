/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::m_internalDistribution()
{
  if(debug) DEBUG;

  Vector2d recmp = (model->rX - des.drXDes/model->wX).head(2);
  MatrixXd Wecmpc = h_weight(recmp);

  VectorXd cal_FcTildeRef =
    constraintModel.Bc.transpose()*fb.cal_Ffb
    - pInv(constraintModel.mbb_CcM, Wecmpc)*(cal_dLCRef + model->cal_GC);
  Vector6d cal_FcTildeHRef = cal_FcTildeRef.tail(6);

  MatrixXd NH = N(constraintModel.mbb_CcM).block(12,0,6,info.constraint->c.all);

  cal_FcaBarRef = pInv(NH)*cal_FcTildeHRef;

  // cal_FcaBarRef = pInv(NH, Wecmpc)*cal_FcTildeHRef;
}
