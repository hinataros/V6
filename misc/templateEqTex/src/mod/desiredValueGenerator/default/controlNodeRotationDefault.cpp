/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::controlNodeRotationDefault(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  // cal_XDes.segment(6*controlNode+3, 3) = model->cal_X.segment(6*controlNode+3, 3);
  cal_VDes.segment(6*controlNode+3, 3) = Vector3d::Zero();
  cal_dVDes.segment(6*controlNode+3, 3) = Vector3d::Zero();
}
