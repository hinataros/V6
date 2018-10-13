/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "rigidBodyModel.hpp"

void RLS::RigidBodyModel::resize()
{
  if(debug) DEBUG;

  mO = 0.;
  rOC = Vector3d::Zero();
  vOC = Vector3d::Zero();

  xiO0 = Vector3d::Zero();
  rO0 = Vector3d::Zero();
  wO0 = Vector3d::Zero();
  vO0 = Vector3d::Zero();

  rO = Vector3d::Zero();
  RO = Matrix3d::Zero();
  vO = Vector3d::Zero();
  wO = Vector3d::Zero();

  fO = Vector3d::Zero();
  nO = Vector3d::Zero();
}
