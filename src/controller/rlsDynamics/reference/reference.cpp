/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reference(const Model &model)
{
  if(debug) DEBUG;

  (this->*baseTranslationReference_ptr)(model.hoap2);
  (this->*baseOrientationReference_ptr)(model.hoap2);
  (this->*controlNodeReference_ptr)(model.hoap2);
  (this->*comReference_ptr)(model.hoap2);
  (this->*dcmReference_ptr)(model.hoap2);
  (this->*externalWrenchReference_ptr)(model.hoap2);

  spatialReference(model);
}
