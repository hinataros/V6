/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::baseRotationDefault(const double &t)
{
  if(debug) DEBUG;

  RBDes = model->RB;
  wBDes = Vector3d::Zero();
  dwBDes = Vector3d::Zero();
}
