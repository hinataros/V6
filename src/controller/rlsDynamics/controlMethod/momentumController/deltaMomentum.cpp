/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::deltaMomentum()
{
  if(debug) DEBUG;

  vrpMomentum();
  baseAngularMomentum();
  centroidalAngularMomentumDamping();

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
