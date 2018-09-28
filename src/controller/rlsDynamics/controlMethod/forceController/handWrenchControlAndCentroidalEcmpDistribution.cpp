/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::handWrenchControlAndCentroidalEcmpDistribution(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // (this->*internalForceController_ptr)(info);

  VectorXd cal_FHcBarRef = (Bc.transpose()*cal_FRef).tail(6);

  MatrixXd bb_CcMH = cal_PcM.block(0,12,6,6);
  VectorXd cal_FCextRef = cal_dLCRef + cal_GC - bb_CcMH*cal_FHcBarRef;
  // VectorXd cal_FCextRef = cal_dLCRef + cal_GC;

  MatrixXd bb_CcMF = cal_PcM.block(0,0,6,12);

  Vector2d rFr = cal_X.segment(0,2);
  Vector2d rFl = cal_X.segment(6,2);

  Vector2d recmp = (rX - drXDes/wX).head(2);

  MatrixXd WecmpF = h_weight(recmp, rFr, rFl);

  VectorXd cal_FFcBarRef = pInv(bb_CcMF, WecmpF)*(cal_FCextRef);

  cal_FcBarRef <<
    cal_FFcBarRef,
    cal_FHcBarRef;
}
