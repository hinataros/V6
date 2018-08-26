/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::comTrajectoryCP(double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[comTrajectoryNum].tw0;
  double twf = sequence[comTrajectoryNum].twf;
  Vector3d initialDes = sequence[comTrajectoryNum].rCpreDes;
  Vector3d finalDes = sequence[comTrajectoryNum].rCf;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    rCDes(i) = des(0) + rC0(i);
    vCDes(i) = des(1);
    dvCDes(i) = des(2);
  }
}
