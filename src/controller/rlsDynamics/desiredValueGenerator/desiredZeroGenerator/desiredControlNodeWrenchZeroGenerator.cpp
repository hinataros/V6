/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::desiredControlNodeWrenchZeroGenerator(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  cal_FDes.segment(6*controlNode, 6) = Vector6d::Zero();
}
