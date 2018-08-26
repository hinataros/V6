/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDcmMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  dcmMomentum(info);
  centroidalAngularMomentum(info);

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
