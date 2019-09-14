 /**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::dcmCP(const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[dcmNum];
  double tf = twf[dcmNum];

  // Vector3d des = Vector3d::Zero();
  // for(int i=0; i<3; i++){
  //   des = makeSpline5(t-t0, tf, rXpreDes(i), rXf(i));
  //
  //   rXDes(i) = des(0) + rX0(i);
  //   drXDes(i) = des(1);
  // }

  Matrix3d des = makeSpline5(t-t0, tf, rXpreDes, rXf);

  rXDes = RB0*des.col(0) + rX0;
  drXDes = RB0*des.col(1);
}
