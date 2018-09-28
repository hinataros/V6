/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseTranslationFBPI(const TreeModel &model)
{
  if(debug) DEBUG;

  erB = rBDes - model.link[model.info.rootNode].r;
  evB = vBDes - model.link[model.info.rootNode].v;

  // velocityController
  vBRef = vBDes + KpvB*erB;

  dvBRef = dvBDes + KdvB*evB + KpvB*erB;
}
