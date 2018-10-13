/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseDcmMomentum()
{
  if(debug) DEBUG;

  dcmMomentum();
  baseAngularMomentum();

  cal_dLBRef <<
    dpRef,
    dlBRef;
}
