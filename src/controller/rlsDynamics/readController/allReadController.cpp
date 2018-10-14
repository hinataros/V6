/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

void RLS::RlsDynamics::allReadController()
{
  if(debug) DEBUG;

  des.readController();
  fb.readController();
  readController();
  ext->readController(this);
}

