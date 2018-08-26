/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::linearMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  dpRef = M*dvCRef;
}
