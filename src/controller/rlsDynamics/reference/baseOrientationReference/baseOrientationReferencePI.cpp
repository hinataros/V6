/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseOrientationReferencePI(const TreeModel &model)
{
  if(debug) DEBUG;

  // smiyahara: オイラー表現の姿勢は計算しといたほうがいいのでは
  RBDes = xi2R(xiBDes);
  // wBDes = dxi2w(dxiBDes, R2xi(model.link[model.info.rootNode].R));
  // dwBDes = ddxi2dw(ddxiBDes, R2xi(model.link[model.info.rootNode].R), w2dxi(model.link[model.info.rootNode].w, R2xi(model.link[model.info.rootNode].R)));

  wBDes = dxi2w(dxiBDes, xiBDes);
  dwBDes = ddxi2dw(ddxiBDes, xiBDes, dxiBDes);

  eoB = 0.5*(cross(model.link[model.info.rootNode].R.col(0))*RBDes.col(0)
             + cross(model.link[model.info.rootNode].R.col(1))*RBDes.col(1)
             + cross(model.link[model.info.rootNode].R.col(2))*RBDes.col(2));
  ewB = wBDes - model.link[model.info.rootNode].w;

  // velocityController
  wBRef = wBDes + KpwB*eoB;

  dwBRef = dwBDes + KdwB*ewB + KpwB*eoB;
}
