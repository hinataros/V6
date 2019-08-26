/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalEcmpInternalDistribution()
{
  if(debug) DEBUG;

  (this->*internalForceController_ptr)();

  Vector2d recmp = (des.rXDes - des.drXDes/model->wXt).head(2);
  // Vector2d recmp = (model->rX - des.drXDes/model->wX).head(2);
  MatrixXd Wecmpc = h_weight(recmp);

  VectorXd Fctemp = pInv(constraintModel.cal_PcM, Wecmpc)*(cal_dLCRef + model->cal_GC);
  cal_FcBarRef = Fctemp;

  if(info.constraint->c.all == 12) { // amiyata
    VectorXd RMomZero = VectorXd::Zero(6), LMomZero = VectorXd::Zero(6);
    RMomZero <<
      VectorXd::Zero(3),
      -Fctemp.segment(3,3);
    LMomZero <<
      VectorXd::Zero(3),
      -Fctemp.segment(9,3);

    if(model->r[0](0) > model->r[1](0))
      cal_FcaBarRef = des.zeroToOne(0)*pInv(N(constraintModel.cal_PcM).block(6,0, 6,12))*(LMomZero);
    else
      cal_FcaBarRef = des.zeroToOne(0)*pInv(N(constraintModel.cal_PcM).block(0,0, 6,12))*(RMomZero);

    cal_FcBarRef =
      pInv(constraintModel.cal_PcM, Wecmpc)*(cal_dLCRef + model->cal_GC)
      + N(constraintModel.cal_PcM)*cal_FcaBarRef;
  }
}
