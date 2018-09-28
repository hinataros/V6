/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::m_internalDistribution(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  Vector2d recmp = (rX - drXDes/wX).head(2);
  MatrixXd Wecmpc = h_weight(recmp);

  VectorXd cal_FcTildeRef = Bc.transpose()*cal_FRef - pInv(cal_PcM, Wecmpc)*(cal_dLCRef + cal_GC);
  Vector6d cal_FcTildeHRef = cal_FcTildeRef.tail(6);

  MatrixXd NH = N(cal_PcM).block(12,0,6,info.contact.c.all);

  // cal_FcaBarRef = pInv(NH)*cal_FcTildeHRef;

  cal_FcaBarRef = pInv(NH, Wecmpc)*cal_FcTildeHRef;
}
