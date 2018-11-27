/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalVrpMomentum()
{
  if(debug) DEBUG;

  vrpMomentum();
  centroidalAngularMomentum();

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
