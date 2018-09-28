 /**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::desiredDcmGeneratorCP(const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredDcmGeneratorNum].tw0;
  double twf = sequence[desiredDcmGeneratorNum].twf;
  Vector3d initialDes = sequence[desiredDcmGeneratorNum].rXpreDes;
  Vector3d finalDes = sequence[desiredDcmGeneratorNum].rXf;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    rXDes(i) = des(0) + rX0(i);
    drXDes(i) = des(1);
  }
}
