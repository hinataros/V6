 /**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::dcmCPabs(const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[dcmNum];
  double tf = twf[dcmNum];

  Vector3d des = Vector3d::Zero();
  for(int i=0; i<3; i++){
    des = makeSpline5(t-t0, tf, rXfinCurabs(i), rXfabs(i));

    rXDes(i) = des(0);
    drXDes(i) = des(1);
  }
}
