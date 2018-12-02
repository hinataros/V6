/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::setConstraintInfo(ConstraintInfo &info)
{
  if(debug) DEBUG;

  this->info.constraint = &info;
}
