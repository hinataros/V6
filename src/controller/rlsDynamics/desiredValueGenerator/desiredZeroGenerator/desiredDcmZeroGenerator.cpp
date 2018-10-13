/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredDcmZeroGenerator(const double &t)
{
  if(debug) DEBUG;

  rXDes = model->rX;
  drXDes = Vector3d::Zero();
}
