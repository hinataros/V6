 /**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmTrajectoryCP(double &t)
{
  if(debug) DEBUG;

  o("dcm");
  gc;

  double tw0 = sequence[dcmTrajectoryNum].tw0;
  double twf = sequence[dcmTrajectoryNum].twf;
  Vector3d initialDes = sequence[dcmTrajectoryNum].rXpreDes;
  Vector3d finalDes = sequence[dcmTrajectoryNum].rXf;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    rXDes(i) = des(0) + rX0(i);
    drXDes(i) = des(1);
  }
}
