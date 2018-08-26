/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseTranslationTrajectoryCP(double &t)
{
  if(debug) DEBUG;

  o("base transdl");
  gc;


  double tw0 = sequence[baseTranslationTrajectoryNum].tw0;
  double twf = sequence[baseTranslationTrajectoryNum].twf;
  Vector3d initialDes = sequence[baseTranslationTrajectoryNum].rBpreDes;
  Vector3d finalDes = sequence[baseTranslationTrajectoryNum].rBf;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    rBDes(i) = des(0) + rB0(i);
    vBDes(i) = des(1);
    dvBDes(i) = des(2);
  }
}
