/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::transform(Model &model)
{
  if(debug) DEBUG;

  model.hoap2.transformMatrix();
  // model.hoap2.jacobian(rkk);
}
