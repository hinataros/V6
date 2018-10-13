/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseMomentum()
{
  if(debug) DEBUG;

  linearMomentum();
  baseAngularMomentum();

  cal_dLBRef <<
    dpRef,
    dlBRef;
}
