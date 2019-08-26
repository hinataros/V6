/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

void RLS::RlsDynamics::initializeStateTrigger()
{
  if(debug) DEBUG;

  // mapping
  stateTrigger_map["default"] = &RLS::RlsDynamics::defaultStateTrigger;
  stateTrigger_map["check foot contact"] = &RLS::RlsDynamics::checkFootContact;
  stateTrigger_map["check contact"] = &RLS::RlsDynamics::checkContact;
  stateTrigger_map["sequence"] = &RLS::RlsDynamics::sequenceTrigger; // amiyata
  stateTrigger_map["continuous sequence"] = &RLS::RlsDynamics::continuousSequence; // amiyata

  // stateTrigger_ptr = stateTrigger_map[config.trigger];

  ext_stateTrigger_map["default"] = &RLS::Ext::defaultStateTrigger;

  // if(extStateTrigger)
  //   ext_stateTrigger_ptr = ext_stateTrigger_map[config.trigger];
}
