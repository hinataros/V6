#include "config.hpp"
#include "common.hpp"

Vector3d RLS::Common::ddxi2dw(Vector3d ddxi, Vector3d xi, Vector3d dxi)
{
  Matrix3d Tw = Matrix3d::Zero();
  Matrix3d dTw = Matrix3d::Zero();
  double sPhi, sTh, cPhi, cTh;

  sPhi = sin(xi(0));
  sTh = sin(xi(1));
  cPhi = cos(xi(0));
  cTh = cos(xi(1));

  Tw <<
    0, -sPhi, cPhi*cTh,
    0, cPhi, sPhi*cTh,
    1, 0, -sTh;

  dTw <<
    0, -cPhi*dxi(0), -sPhi*cTh*dxi(0) - cPhi*sTh*dxi(1),
    0, -sPhi*dxi(1), cPhi*cTh*dxi(0) - sPhi*sTh*dxi(1),
    0, 0, -cTh*dxi(1);

  return Tw*ddxi + dTw*dxi;
}
