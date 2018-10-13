/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredBaseTranslationZeroGenerator(const double &t)
{
  if(debug) DEBUG;

  rBDes = model->rB;
  vBDes = Vector3d::Zero();
  dvBDes = Vector3d::Zero();
}
