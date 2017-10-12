#include "config.hpp"
#include "common.hpp"

Vector3d RLS::Common::w2dxi(Vector3d w, Vector3d xi)
{
  Matrix3d Tw = Matrix3d::Zero();
  double sPhi, sTh, cPhi, cTh;

  sPhi = sin(xi(0));
  sTh = sin(xi(1));
  cPhi = cos(xi(0));
  cTh = cos(xi(1));

  Tw <<
    0, -sPhi, cPhi*cTh,
    0, cPhi, sPhi*cTh,
    1, 0, -sTh;

  return Tw.inverse()*w;
}
