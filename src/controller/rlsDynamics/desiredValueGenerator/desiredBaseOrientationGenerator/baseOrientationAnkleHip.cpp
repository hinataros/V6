/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::baseOrientationAnkleHip(Config &config,Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, xiBpreDes(i), xiBf(i));
    xiBDes(i) = des(0) + xiB0(i);
    dxiBDes(i) = des(1);
    ddxiBDes(i) = des(2);
  }

  // smiyahara: オイラー表現の姿勢は計算しといたほうがいいのでは
  RBDes = xi2R(xiBDes);
  wBDes = dxi2w(dxiBDes, R2xi(model.hoap2.limb[0].node[0].R));
  dwBDes = ddxi2dw(ddxiBDes, R2xi(model.hoap2.limb[0].node[0].R), w2dxi(model.hoap2.limb[0].node[0].w, R2xi(model.hoap2.limb[0].node[0].R)));

  eoB = 0.5*(cross(model.hoap2.limb[0].node[0].R.col(0))*RBDes.col(0)
             + cross(model.hoap2.limb[0].node[0].R.col(1))*RBDes.col(1)
             + cross(model.hoap2.limb[0].node[0].R.col(2))*RBDes.col(2));
  ewB = wBDes - model.hoap2.limb[0].node[0].w;

  // velocityController
  wBRef = wBDes + KpwB*eoB;

  dwBRef = dwBDes + KdwB*ewB + KpwB*eoB;

  // if(info.sim.phase==5){
  //   for(int i=0; i<3; i++){
  //     des = makeSpline5(t-info.sim.tw0, 4., xiBpreState(i), dxiBpreState(i), 0., 0., 0., 0.);
  //     xiBDes(i) = des(0) + xiB0(i);
  //     dxiBDes(i) = des(1);
  //     ddxiBDes(i) = des(2);
  //   }

  //   // smiyahara: オイラー表現の姿勢は計算しといたほうがいいのでは
  //   RBDes = xi2R(xiBDes);
  //   wBDes = dxi2w(dxiBDes, R2xi(model.hoap2.limb[0].node[0].R));
  //   dwBDes = ddxi2dw(ddxiBDes, R2xi(model.hoap2.limb[0].node[0].R), w2dxi(model.hoap2.limb[0].node[0].w, R2xi(model.hoap2.limb[0].node[0].R)));

  //   eoB = 0.5*(cross(model.hoap2.limb[0].node[0].R.col(0))*RBDes.col(0)
  //              + cross(model.hoap2.limb[0].node[0].R.col(1))*RBDes.col(1)
  //              + cross(model.hoap2.limb[0].node[0].R.col(2))*RBDes.col(2));
  //   ewB = wBDes - model.hoap2.limb[0].node[0].w;

  //   dwBRef = dwBDes + KdwB*ewB + KpwB*eoB;
  // }
}
