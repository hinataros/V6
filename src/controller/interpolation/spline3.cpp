/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "spline3.hpp"

Vector3d RLS::Spline3::makeSpline3(double t, double tf, double r0, double rf)
{
  return makeSpline3(t, tf, r0, 0., rf, 0.);
}

Vector3d RLS::Spline3::makeSpline3(double t, double tf, double xi0, double dxi0, double xif, double dxif)
{
  if(!round_cast(tf, 3)){
    par.head(2) <<
      xi0,
      dxi0;

    return par;
  }

  a.head(4) <<
    xi0,
    dxi0,
    (-3.*xi0 - 2.*dxi0*tf + 3.*xif - dxif*tf) / (tf*tf),
    (2.*xi0 + dxi0*tf - 2.*xif + dxif*tf) / (tf*tf*tf);

  par(0) = a(0) + a(1)*t + a(2)*t*t + a(3)*t*t*t;

  par(1) = a(1) + 2.*a(2)*t + 3.*a(3)*t*t;

  return par;
}
