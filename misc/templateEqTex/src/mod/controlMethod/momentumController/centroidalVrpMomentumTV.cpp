/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalVrpMomentumTV()
{
  if(debug) DEBUG;

  vrpMomentumwXt();
  centroidalAngularMomentum();

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
