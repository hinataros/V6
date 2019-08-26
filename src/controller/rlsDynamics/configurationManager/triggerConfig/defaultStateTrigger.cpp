/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::defaultStateTrigger(const double &t, const struct State &state)
{
  if(debug) DEBUG;

  return 0;
}
