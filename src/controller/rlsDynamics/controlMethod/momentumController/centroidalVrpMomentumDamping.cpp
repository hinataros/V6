/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalVrpMomentumDamping()
{
  if(debug) DEBUG;

  vrpMomentum();
  centroidalAngularMomentumDamping();

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
