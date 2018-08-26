/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::jointSpace(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  tau = Mth*ddthRef + cth + gth;
}
