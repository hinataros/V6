#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::baseReference(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, rBtemp(i), rBf(i));
    rBDes(i) = des(0) + rB0(i);
    vBDes(i) = des(1);
  }

  erB = rBDes - model.limb[0].node[0].r;

  vBRef = vBDes + kpvB*erB;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, xiBtemp(i), xiBf(i));
    xiBDes(i) = des(0) + xiB0(i);
    dxiBDes(i) = des(1);
  }

  // smiyahara: オイラー表現の姿勢は計算しといたほうがいい
  RBDes = xi2R(xiBDes);
  wBDes = dxi2w(dxiBDes, R2xi(model.limb[0].node[0].R));

  eoB = 0.5*(cross(model.limb[0].node[0].R.col(0))*RBDes.col(0)
	     + cross(model.limb[0].node[0].R.col(1))*RBDes.col(1)
	     + cross(model.limb[0].node[0].R.col(2))*RBDes.col(2));

  wBRef = wBDes + kpwB*eoB;

  cal_VBRef <<
    vBRef,
    wBRef;
}
