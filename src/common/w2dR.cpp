/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

Matrix3d RLS::Common::w2dR(Vector3d w, Matrix3d R)
{
  return cross(w)*R;
}
