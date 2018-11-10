/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::controlNodeMotionPI()
{
  if(debug) DEBUG;

  for(int i=0; i<info->controlNodeNum; i++){
    Quaternion4d qe = Quaternion4d::R2q(model->R[i]);

    cal_Ep.segment(6*i, 6) <<
      des->rDes[i] - model->r[i],
      qe.w*des->qDes[i].v - des->qDes[i].w*qe.v - cross(des->qDes[i].v)*qe.v;
      // orientationError(des->RDes[i], model->R[i]);
  }

  cal_Ev = des->cal_VDes - model->cal_V;

  // velocityController
  cal_Vfb = des->cal_VDes + Kpv*cal_Ep;

  cal_dVfb = des->cal_dVDes + Kdv*cal_Ev + Kpv*cal_Ep;
}
