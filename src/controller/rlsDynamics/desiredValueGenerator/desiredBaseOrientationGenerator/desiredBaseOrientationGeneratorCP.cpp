/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredBaseOrientationGeneratorCP(const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredBaseOrientationGeneratorNum].tw0;
  double twf = sequence[desiredBaseOrientationGeneratorNum].twf;
  Vector3d initialDes = sequence[desiredBaseOrientationGeneratorNum].xiBpreDes;
  Vector3d finalDes = sequence[desiredBaseOrientationGeneratorNum].xiBf;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));
    xiBDes(i) = des(0) + xiB0(i);
    dxiBDes(i) = des(1);
    ddxiBDes(i) = des(2);
  }

  RBDes = xi2R(xiBDes);

  // smiyahara: オイラー表現の姿勢は計算しといたほうがいいのでは
  // wBDes = dxi2w(dxiBDes, R2xi(this->model.RB));
  // dwBDes = ddxi2dw(ddxiBDes, R2xi(this->model.RB), w2dxi(model.link[model.info.rootNode].w, R2xi(this->model.RB)));

  wBDes = dxi2w(dxiBDes, xiBDes);
  dwBDes = ddxi2dw(ddxiBDes, xiBDes, dxiBDes);
}
