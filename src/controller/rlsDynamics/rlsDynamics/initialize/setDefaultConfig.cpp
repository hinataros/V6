/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::setDefaultConfig()
{
  if(debug) DEBUG;

  config.controlModel = "default";
  config.controlNodeNum = 0;

  config.input = "no input";
  // config.driven = "flow";
  // config.trigger = "default";

  extStateTrigger = false;
}
