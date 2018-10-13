/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredExternalWrenchGeneratorCP(const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredExternalWrenchGeneratorNum].tw0;
  double twf = sequence[desiredExternalWrenchGeneratorNum].twf;
  Vector6d initialDes = sequence[desiredExternalWrenchGeneratorNum].cal_FextpreDes;
  Vector6d finalDes = sequence[desiredExternalWrenchGeneratorNum].cal_Fextf;

  for(int i=0; i<6; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    cal_FextDes(i) = des(0);
  }
}
