/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalMomentum()
{
  if(debug) DEBUG;

  linearMomentum();
  centroidalAngularMomentum();

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
