#include "config.hpp"
#include "common.hpp"

Matrix3d RLS::Common::xi2R(Vector3d xi)
{
  Vector3d sxi = Vector3d::Zero();
  Vector3d cxi = Vector3d::Zero();

  Matrix3d R = Matrix3d::Zero();

  sxi <<
    sin(xi(0)),
    sin(xi(1)),
    sin(xi(2));

  cxi <<
    cos(xi(0)),
    cos(xi(1)),
    cos(xi(2));

  // ZYX
  R <<
    cxi(0)*cxi(1), cxi(0)*sxi(1)*sxi(2)-sxi(0)*cxi(2), cxi(0)*sxi(1)*cxi(2)+sxi(0)*sxi(2),
    sxi(0)*cxi(1), sxi(0)*sxi(1)*sxi(2)+cxi(0)*cxi(2), sxi(0)*sxi(1)*cxi(2)-cxi(0)*sxi(2),
    -sxi(1), cxi(1)*sxi(2), cxi(1)*cxi(2);

  //ZYZ
  // R <<
  //   cxi(0)*cxi(1)*cxi(2)-sxi(0)*sxi(2), -cxi(0)*cxi(1)*sxi(2)-sxi(0)*cxi(2), cxi(0)*sxi(1),
  //   sxi(0)*cxi(1)*cxi(2)-cxi(0)*sxi(2), -sxi(0)*cxi(1)*sxi(2)-cxi(0)*cxi(2), sxi(0)*sxi(1),
  //   -sxi(1)*cxi(2), sxi(1)*sxi(2), cxi(1);

  return R;
}
