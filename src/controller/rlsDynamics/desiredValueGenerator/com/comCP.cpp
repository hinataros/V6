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

  // Vector3d des = Vector3d::Zero();
  // for(int i=0; i<3; i++){
  //   des = makeSpline5(t-t0, tf, rCpreDes(i), rCf(i));
  //
  //   rCDes(i) = des(0) + rC0(i);
  //   vCDes(i) = des(1);
  //   dvCDes(i) = des(2);
  // }

  Matrix3d des = makeSpline5(t-t0, tf, rCpreDes, rCf);

  rCDes = RB0*des.col(0) + rC0;
  vCDes = RB0*des.col(1);
  dvCDes = RB0*des.col(2);
}
