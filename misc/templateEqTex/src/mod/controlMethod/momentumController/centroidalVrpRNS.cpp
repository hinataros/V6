/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalVrpRNS()
{
  if(debug) DEBUG;

  vrpMomentum();
  reactionNullSpaceMomentum();

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
