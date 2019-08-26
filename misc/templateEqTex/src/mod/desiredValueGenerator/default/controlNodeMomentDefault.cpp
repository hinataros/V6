/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::controlNodeMomentDefault(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  cal_FDes.segment(6*controlNode+3, 3) = Vector3d::Zero();
}
