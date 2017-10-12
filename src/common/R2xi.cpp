#include "config.hpp"
#include "common.hpp"

Vector3d RLS::Common::R2xi(Matrix3d R)
{
  Vector3d xi = Vector3d::Zero();
  double phi, th, psi;

  // double thr = 1.e-16;
  // for(int i=0; i<3; i++)
  //   for(int j=0; j<3; j++)
  //     if(R(i,j)<thr)
  // 	R(i,j) = 0.;

  //ZYX
  double x = 1-R(2,0)*R(2,0);
  if(x < 0.)
    th = atan2(-R(2,0), 0.);
  else
    th = atan2(-R(2,0), sqrt(x));

  double s = math("s", 1, th);
  if(s<1.e-3)
    s=0.;

  if (s > 0.) {
    phi = atan2(R(1,0), R(0,0));
    psi = atan2(R(2,1), R(2,2));

  } else if (s < 0.) {
    phi = atan2(-R(1,0), -R(0,0));
    psi = atan2(-R(2,1), -R(2,2));

  } else {
    phi = 0.;
    psi = 0.;
  }

  // if (phi <= -M_PI || phi >= M_PI) phi = 0.;
  // if (psi <= -M_PI || psi >= M_PI) psi = 0.;

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
