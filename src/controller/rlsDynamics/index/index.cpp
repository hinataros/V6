/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::index(const Model &model)
{
  if(debug) DEBUG;

  cop(model.hoap2);
  cmp(model.hoap2);
  dcm(model.hoap2);
}
