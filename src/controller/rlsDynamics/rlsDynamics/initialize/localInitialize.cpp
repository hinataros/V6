/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::localInitialize()
{
  if(debug) DEBUG;

  // high gain control
  thDes = model->th0;
}
