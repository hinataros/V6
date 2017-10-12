#include "config.hpp"
#include "spline5.hpp"

Vector3d RLS::Spline5::makeSpline5(double t, double tf, double r0, double rf){
  return makeSpline5(t, tf, r0, 0., 0., rf, 0., 0.);
}

Vector3d RLS::Spline5::makeSpline5(double t, double tf, double xi0, double dxi0, double ddxi0, double xif, double dxif, double ddxif)
{
  a <<
    xi0,
    dxi0,
    ddxi0/2.,
    (20.*xif - 20.*xi0 - (8.*dxif + 12.*dxi0)*tf - (3.*ddxi0 - ddxif)*tf*tf) / (2.*tf*tf*tf),
    (30.*xi0 - 30.*xif + (14.*dxif + 16.*dxi0)*tf + (3.*ddxi0 - 2.*ddxif)*tf*tf) / (2.*tf*tf*tf*tf),
    (12.*xif - 12.*xi0 - (6.*dxif + 6.*dxi0)*tf - (ddxi0 - ddxif)*tf*tf) / (2.*tf*tf*tf*tf*tf );

  par(0) = a(0)
    + a(1) * t
    + a(2) * t*t
    + a(3) * t*t*t
    + a(4) * t*t*t*t
    + a(5) * t*t*t*t*t;

  par(1) = a(1)
    + 2.*a(2) * t
    + 3.*a(3) * t*t
    + 4.*a(4) * t*t*t
    + 5.*a(5) * t*t*t*t;

  par(2) = 2.*a(2)
    +  6.*a(3) * t
    + 12.*a(4) * t*t
    + 20.*a(5) * t*t*t;

  return par;
}
