/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::externalWrenchCP(const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[externalWrenchNum];
  double tf = twf[externalWrenchNum];

  Vector3d des = Vector3d::Zero();
  for(int i=0; i<6; i++){
    des = makeSpline5(t-t0, tf, cal_FextpreDes(i), cal_Fextf(i));

    cal_FextDes(i) = des(0);
  }
}
