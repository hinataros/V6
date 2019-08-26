/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::comCP(const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[comNum];
  double tf = twf[comNum];

  Vector3d des = Vector3d::Zero();
  for(int i=0; i<3; i++){
    des = makeSpline5(t-t0, tf, rCpreDes(i), rCf(i));

    rCDes(i) = des(0) + rC0(i);
    vCDes(i) = des(1);
    dvCDes(i) = des(2);
  }
}
