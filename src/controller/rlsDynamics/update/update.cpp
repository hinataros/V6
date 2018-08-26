/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::update(Model &model)
{
  if(debug) DEBUG;

  transform(model);
  decompose(model);
  objective(model.hoap2.info);
  rename(model);
}
