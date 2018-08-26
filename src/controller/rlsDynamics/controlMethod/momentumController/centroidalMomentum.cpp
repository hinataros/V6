/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  linearMomentum(info);
  centroidalAngularMomentum(info);

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
