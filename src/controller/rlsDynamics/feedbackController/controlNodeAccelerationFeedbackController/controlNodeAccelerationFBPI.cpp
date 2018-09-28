/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::controlNodeAccelerationFBPI(const TreeModel &model)
{
  if(debug) DEBUG;

  for(int i=0; i<model.info.controlNodeNum; i++){
    // cal_VDes.segment(6*i, 6) <<
    //   cal_VxiDes.segment(6*i, 3),
    //   dxi2w(cal_VxiDes.segment(6*i+3, 3), cal_X.segment(6*i+3, 3));
    // cal_dVDes.segment(6*i, 6) <<
    //   cal_dVxiDes.segment(6*i, 3),
    //   ddxi2dw(cal_dVxiDes.segment(6*i+3, 3), cal_X.segment(6*i+3, 3), w2dxi(cal_V.segment(6*i+3, 3), cal_X.segment(6*i+3, 3)));

    cal_VDes.segment(6*i, 6) <<
      cal_VxiDes.segment(6*i, 3),
      dxi2w(cal_VxiDes.segment(6*i+3, 3), cal_XDes.segment(6*i+3, 3));
    cal_dVDes.segment(6*i, 6) <<
      cal_dVxiDes.segment(6*i, 3),
      ddxi2dw(cal_dVxiDes.segment(6*i+3, 3), cal_XDes.segment(6*i+3, 3), cal_VxiDes.segment(6*i+3, 3));

    cal_Ep.segment(6*i, 6) <<
      cal_XDes.segment(6*i, 3) - cal_X.segment(6*i, 3),
      0.5*(cross(model.all.Rk.block(6*i,6*i,3,3).col(0))*xi2R(cal_XDes.segment(6*i+3, 3)).col(0)
           + cross(model.all.Rk.block(6*i,6*i,3,3).col(1))*xi2R(cal_XDes.segment(6*i+3, 3)).col(1)
           + cross(model.all.Rk.block(6*i,6*i,3,3).col(2))*xi2R(cal_XDes.segment(6*i+3, 3)).col(2));
  }

  cal_Ev = cal_VDes - cal_V;

  // velocityController
  cal_VRef = cal_VDes + Kpv*cal_Ep;

  cal_dVRef = cal_dVDes + Kdv*cal_Ev + Kpv*cal_Ep;
}
