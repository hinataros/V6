/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::endEffectorReference(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<6*info.value.joint; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, cal_XpreDes(i), cal_Xf(i));

    cal_XDes(i) = des(0) + cal_X0(i);
    cal_VxiDes(i) = des(1);
    cal_dVxiDes(i) = des(2);
  }

  for(int i=1; i<info.value.node; i++){
    cal_VDes.segment(6*(i-1), 6) <<
      cal_VxiDes.segment(6*(i-1), 3),
      dxi2w(cal_VxiDes.segment(6*(i-1)+3, 3), cal_X.segment(6*(i-1)+3, 3));
    cal_dVDes.segment(6*(i-1), 6) <<
      cal_dVxiDes.segment(6*(i-1), 3),
      ddxi2dw(cal_dVxiDes.segment(6*(i-1)+3, 3), cal_X.segment(6*(i-1)+3, 3), w2dxi(cal_V.segment(6*(i-1)+3, 3), cal_X.segment(6*(i-1)+3, 3)));

    cal_Ep.segment(6*(i-1), 6) <<
      cal_XDes.segment(6*(i-1), 3) - cal_X.segment(6*(i-1), 3),
      0.5*(cross(model.hoap2.limb[i].node[info.limb[i].dof].R.col(0))*xi2R(cal_XDes.segment(6*(i-1)+3, 3)).col(0)
	      + cross(model.hoap2.limb[i].node[info.limb[i].dof].R.col(1))*xi2R(cal_XDes.segment(6*(i-1)+3, 3)).col(1)
	      + cross(model.hoap2.limb[i].node[info.limb[i].dof].R.col(2))*xi2R(cal_XDes.segment(6*(i-1)+3, 3)).col(2));
  }
  cal_Ev = cal_VDes - cal_V;

  // velocityController
  cal_VRef = cal_VDes + Kpv*cal_Ep;

  cal_dVRef = cal_dVDes + Kdv*cal_Ev + Kpv*cal_Ep;
}
