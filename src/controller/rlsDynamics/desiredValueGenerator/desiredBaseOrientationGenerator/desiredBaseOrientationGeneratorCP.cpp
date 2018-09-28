/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::desiredBaseOrientationGeneratorCP(const double &t)
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
}
