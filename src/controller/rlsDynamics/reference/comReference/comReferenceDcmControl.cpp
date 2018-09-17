/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::comReferenceDcmControl(const TreeModel &model)
{
  if(debug) DEBUG;

  dvCRef = wX*(drXRef - model.all.vC);
}
