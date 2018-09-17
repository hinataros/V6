/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::noTrigger(const Model &model, const double &t)
{
  return 0;
}
