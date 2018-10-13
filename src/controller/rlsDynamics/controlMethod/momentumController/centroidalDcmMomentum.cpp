/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalDcmMomentum()
{
  if(debug) DEBUG;

  dcmMomentum();
  centroidalAngularMomentum();

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
