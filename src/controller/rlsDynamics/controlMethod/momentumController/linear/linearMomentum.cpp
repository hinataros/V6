/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::linearMomentum()
{
  if(debug) DEBUG;

  dpRef = model->M*fb.dvCfb;
}
