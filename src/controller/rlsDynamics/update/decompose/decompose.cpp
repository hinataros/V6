/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decompose(const Model &model)
{
  if(debug) DEBUG;

  contactCoordinate(model);
  basis();

  decomposeBase(model);
  decomposeMix(model);
}
