/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseOrientationTrajectoryCP(double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[baseOrientationTrajectoryNum].tw0;
  double twf = sequence[baseOrientationTrajectoryNum].twf;
  Vector3d initialDes = sequence[baseOrientationTrajectoryNum].xiBpreDes;
  Vector3d finalDes = sequence[baseOrientationTrajectoryNum].xiBf;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));
    xiBDes(i) = des(0) + xiB0(i);
    dxiBDes(i) = des(1);
    ddxiBDes(i) = des(2);
  }
}
