/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeTriggerMap(const string &customTriggerName)
{
  if(debug) DEBUG;

  // mapping
  map_customTrigger["default"] = &RLS::RlsDynamics::noTrigger;
  map_customTrigger["check contact"] = &RLS::RlsDynamics::checkContact;

  customTrigger_ptr = map_customTrigger[customTriggerName];
}
