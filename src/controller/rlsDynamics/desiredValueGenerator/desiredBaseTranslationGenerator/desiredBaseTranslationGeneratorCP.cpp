/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredBaseTranslationGeneratorCP(const double &t)
{
  if(debug) DEBUG;

  double tw0 = sequence[desiredBaseTranslationGeneratorNum].tw0;
  double twf = sequence[desiredBaseTranslationGeneratorNum].twf;
  Vector3d initialDes = sequence[desiredBaseTranslationGeneratorNum].rBpreDes;
  Vector3d finalDes = sequence[desiredBaseTranslationGeneratorNum].rBf;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-tw0, twf, initialDes(i), finalDes(i));

    rBDes(i) = des(0) + rB0(i);
    vBDes(i) = des(1);
    dvBDes(i) = des(2);
  }
}
