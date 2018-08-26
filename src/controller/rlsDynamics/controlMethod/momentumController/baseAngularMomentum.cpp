/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseAngularMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  dlBRef =
    -M*cross(rB2C).transpose()*dvCRef + IC*dwBRef
    -M*cross(drB2C).transpose()*wB + dIC*wB;
}
