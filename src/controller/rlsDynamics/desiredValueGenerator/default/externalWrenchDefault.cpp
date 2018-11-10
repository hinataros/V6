/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::externalWrenchDefault(const double &t)
{
  if(debug) DEBUG;

  cal_FextDes = Vector6d::Zero();
}
