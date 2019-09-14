/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::baseTranslationCP(const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[baseTranslationNum];
  double tf = twf[baseTranslationNum];

  // Vector3d des = Vector3d::Zero();
  // for(int i=0; i<3; i++){
  //   des = makeSpline5(t-t0, tf, rBpreDes(i), rBf(i));
  //
  //   rBDes(i) = des(0) + rB0(i);
  //   vBDes(i) = des(1);
  //   dvBDes(i) = des(2);
  // }

  Matrix3d des = makeSpline5(t-t0, tf, rBpreDes, rBf);

  rBDes = RB0*des.col(0) + rB0;
  vBDes = RB0*des.col(1);
  dvBDes = RB0*des.col(2);
}
