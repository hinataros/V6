#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseReference(Config &config,Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, rBtemp(i), rBf(i));
    rBDes(i) = des(0) + rB0(i);
    vBDes(i) = des(1);
    dvBDes(i) = des(2);
  }

  erB = rBDes - model.limb[0].node[0].r;
  evB = vBDes - model.limb[0].node[0].v;

  dvBRef = dvBDes + kdvB*evB + kpvB*erB;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, xiBtemp(i), xiBf(i));
    xiBDes(i) = des(0) + xiB0(i);
    dxiBDes(i) = des(1);
    ddxiBDes(i) = des(2);
  }

  // smiyahara: オイラー表現の姿勢は計算しといたほうがいいのでは
  RBDes = xi2R(xiBDes);
  wBDes = dxi2w(dxiBDes, R2xi(model.limb[0].node[0].R));
  dwBDes = ddxi2dw(ddxiBDes, R2xi(model.limb[0].node[0].R), w2dxi(model.limb[0].node[0].w, R2xi(model.limb[0].node[0].R)));

  // smiyahara: errorがphase変更時で消える問題
  eoB = 0.5*(cross(model.limb[0].node[0].R.col(0))*RBDes.col(0)
	     + cross(model.limb[0].node[0].R.col(1))*RBDes.col(1)
	     + cross(model.limb[0].node[0].R.col(2))*RBDes.col(2));
  ewB = wBDes - model.limb[0].node[0].w;

  dwBRef = dwBDes + kdwB*ewB + kpwB*eoB;
}
