/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredComZeroGenerator(const double &t)
{
  if(debug) DEBUG;

  rCDes = model->rC;
  vCDes = Vector3d::Zero();
  dvCDes = Vector3d::Zero();
}
