#include "config.hpp"
#include "common.hpp"

Matrix3d RLS::Common::cross(Vector3d x)
{
  Matrix3d a = Matrix3d::Zero();

  a <<
    0    ,-x(2), x(1),
    x(2) ,    0,-x(0),
    -x(1), x(0),    0;

  return a;
}
