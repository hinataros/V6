 /**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmFBPI(const TreeModel &model)
{
  if(debug) DEBUG;

  eX = rXDes - rX;

  drXRef = drXDes + KX*eX;
}
