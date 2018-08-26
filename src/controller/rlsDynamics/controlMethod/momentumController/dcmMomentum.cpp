/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  Vector3d rvrpRef = rX - drXRef/wX;

  dpRef = M*wX*wX*(rC - rvrpRef);
}
