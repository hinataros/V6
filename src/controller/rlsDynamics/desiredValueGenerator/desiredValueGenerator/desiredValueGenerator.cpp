/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredValueGenerator(const double &t)
{
  if(debug) DEBUG;

  (this->*desiredBaseTranslationGenerator_ptr)(t);
  (this->*desiredBaseOrientationGenerator_ptr)(t);

  for(int i=0; i<info->controlNodeNum; i++){
    (this->*desiredControlNodeMotionGenerator_ptr[i])(i, t);
    (this->*desiredControlNodeForceGenerator_ptr[i])(i, t);
  }

  (this->*desiredComGenerator_ptr)(t);
  (this->*desiredDcmGenerator_ptr)(t);
  (this->*desiredExternalWrenchGenerator_ptr)(t);
}
