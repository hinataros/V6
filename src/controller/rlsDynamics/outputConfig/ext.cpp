/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

void RLS::RlsDynamics::outputExtConfig()
{
  if(debug) DEBUG;

  ext->output(this);
  extList = ext->outputList;
}
