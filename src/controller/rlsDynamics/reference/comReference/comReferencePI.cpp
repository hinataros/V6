/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::comReferencePI(const TreeModel &model)
{
  if(debug) DEBUG;

  erC = rCDes - model.all.rC;
  evC = vCDes - model.all.vC;

  // velocityController
  vCRef = vCDes + KpC*erC;

  dvCRef = dvCDes + KdC*evC + KpC*erC;
}
