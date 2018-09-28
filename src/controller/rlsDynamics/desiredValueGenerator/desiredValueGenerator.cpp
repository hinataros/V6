/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::desiredValueGenerator(const int &controlNodeNum, const double &t)
{
  if(debug) DEBUG;

  (this->*desiredBaseTranslationGenerator_ptr)(t);
  (this->*desiredBaseOrientationGenerator_ptr)(t);

  for(int i=0; i<controlNodeNum; i++){
    (this->*desiredControlNodeAccelerationGenerator_ptr[i])(i, t);
    (this->*desiredControlNodeWrenchGenerator_ptr[i])(i, t);
  }

  (this->*desiredComGenerator_ptr)(t);
  (this->*desiredDcmGenerator_ptr)(t);
  (this->*desiredExternalWrenchGenerator_ptr)(t);
}
