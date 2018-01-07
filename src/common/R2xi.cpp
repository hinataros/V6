/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

Vector3d RLS::Common::R2xi(Matrix3d R)
{
  Vector3d xi = Vector3d::Zero();
  double phi, th, psi;

  //ZYX
  double x = 1-R(2,0)*R(2,0);

  double s = -R(2,0);
  double c;

  if(x<0.)
    c = 0.;
  else
    c = sqrt(x);

  th = atan2(s, c);

  if(c>=0.){
    phi = atan2(R(1,0), R(0,0));
    psi = atan2(R(2,1), R(2,2));

  }else if(c<0.){
    phi = atan2(-R(1,0), -R(0,0));
    psi = atan2(-R(2,1), -R(2,2));

  }else{
    phi = 0.;
    psi = 0.;
  }

  //ZYZ
  // theta = atan2(sqrt(1-R(2,2)*R(2,2)), R(2,2));

  // double s = math("s", 1, theta);

  // if (s > 0.) {
  //   phi = atan2(R(1,2), R(0,2));
  //   psi = atan2(R(2,1), -R(2,0));

  // } else if (s < 0.) {
  //   phi = atan2(-R(1,2), -R(0,2));
  //   psi = atan2(-R(2,1), R(2,0));

  // } else {
  //   phi = 0.;
  //   psi = 0.;
  //   // cout << "theta=0: Gimbal lock" << endl;
  // }

  xi <<
    phi,
    th,
    psi;

  return xi;
}
