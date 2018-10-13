/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::controlNodeAccelerationFBPI()
{
  if(debug) DEBUG;

  for(int i=0; i<info->controlNodeNum; i++){
    // cal_Ep.segment(6*i, 6) <<
    //   des->cal_XDes.segment(6*i, 3) - model->cal_X.segment(6*i, 3),
    //   0.5*(cross(model->bb_Rk.block(6*i,6*i,3,3).col(0))*xi2R(des->cal_XDes.segment(6*i+3, 3)).col(0)
    //        + cross(model->bb_Rk.block(6*i,6*i,3,3).col(1))*xi2R(des->cal_XDes.segment(6*i+3, 3)).col(1)
    //        + cross(model->bb_Rk.block(6*i,6*i,3,3).col(2))*xi2R(des->cal_XDes.segment(6*i+3, 3)).col(2));

    cal_Ep.segment(6*i, 6) <<
      des->cal_XDes.segment(6*i, 3) - model->cal_X.segment(6*i, 3),
      0.5*(cross(xi2R(model->cal_X.segment(6*i+3, 3)).col(0))*xi2R(des->cal_XDes.segment(6*i+3, 3)).col(0)
           + cross(xi2R(model->cal_X.segment(6*i+3, 3)).col(1))*xi2R(des->cal_XDes.segment(6*i+3, 3)).col(1)
           + cross(xi2R(model->cal_X.segment(6*i+3, 3)).col(2))*xi2R(des->cal_XDes.segment(6*i+3, 3)).col(2));
  }

  cal_Ev = des->cal_VDes - model->cal_V;

  // velocityController
  cal_Vfb = des->cal_VDes + Kpv*cal_Ep;

  cal_dVfb = des->cal_dVDes + Kdv*cal_Ev + Kpv*cal_Ep;
}
