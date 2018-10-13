/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredBaseOrientationZeroGenerator(const double &t)
{
  if(debug) DEBUG;

  xiBDes = model->xiB;
  dxiBDes = Vector3d::Zero();
  ddxiBDes = Vector3d::Zero();
}
