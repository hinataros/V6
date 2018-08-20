/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcm(const TreeModel &model)
{
  if(debug) DEBUG;

  wX = sqrt(g/rC0(2));

  rX = model.all.rC + (model.all.vC/wX);
}
