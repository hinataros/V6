#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::endEffectorReference(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<6*info.value.joint; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, cal_Xtemp(i), cal_Xf(i));

    cal_XDes(i) = des(0) + cal_X0(i);
    cal_VDes(i) = des(1);
  }

  cal_VRef = cal_VDes;
}
