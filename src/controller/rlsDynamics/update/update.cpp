/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::update()
{
  if(debug) DEBUG;

  decompose();
  objective();
  rename();
}
