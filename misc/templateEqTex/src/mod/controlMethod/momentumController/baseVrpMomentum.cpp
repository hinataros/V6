/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseVrpMomentum()
{
  if(debug) DEBUG;

  vrpMomentum();
  baseAngularMomentum();

  cal_dLBRef <<
    dpRef,
    dlBRef;
}
