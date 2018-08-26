/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::crb(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  tau = MthHat*ddthRef + cthHat - cal_JcHat.transpose()*cal_FcBarRef;
}
