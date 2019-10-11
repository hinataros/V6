/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::externalWrenchStep(const double &t)
{
  if(debug) DEBUG;

    cal_FextDes = cal_Fextf;
}
