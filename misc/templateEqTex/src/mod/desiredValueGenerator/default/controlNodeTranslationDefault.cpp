/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::controlNodeTranslationDefault(const int &controlNode, const double &t)
{
  if(debug) DEBUG;

  rDes[controlNode] = model->r[controlNode];
  cal_VDes.segment(6*controlNode, 3) = Vector3d::Zero();
  cal_dVDes.segment(6*controlNode, 3) = Vector3d::Zero();
}
