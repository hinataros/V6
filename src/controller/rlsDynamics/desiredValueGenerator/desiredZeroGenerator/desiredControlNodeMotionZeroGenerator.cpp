/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredControlNodeMotionZeroGenerator(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  cal_XDes.segment(6*controlNode, 6) = model->cal_X.segment(6*controlNode, 6);
  cal_VxiDes.segment(6*controlNode, 6) = Vector6d::Zero();
  cal_dVxiDes.segment(6*controlNode, 6) = Vector6d::Zero();
}
