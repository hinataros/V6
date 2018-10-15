/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "rigidBodyModel.hpp"

void RLS::RigidBodyModel::resize()
{
  if(debug) DEBUG;

  m = 0.;

  xiR0 = Vector3d::Zero();
  rR0 = Vector3d::Zero();
  wR0 = Vector3d::Zero();
  vR0 = Vector3d::Zero();

  rR = Vector3d::Zero();
  RR = Matrix3d::Zero();
  vR = Vector3d::Zero();
  wR = Vector3d::Zero();

  fR = Vector3d::Zero();
  nR = Vector3d::Zero();

  rC = Vector3d::Zero();
  vC = Vector3d::Zero();
}
