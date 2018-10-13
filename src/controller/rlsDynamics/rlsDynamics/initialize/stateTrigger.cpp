/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeStateTrigger()
{
  if(debug) DEBUG;

  state.num = -1; //smiyahara: 初期化をconfigurationManagerでやるため

  // mapping
  map_customTrigger["default"] = &RLS::RlsDynamics::noTrigger;
  map_customTrigger["check foot contact"] = &RLS::RlsDynamics::checkFootContact;
  map_customTrigger["check contact"] = &RLS::RlsDynamics::checkContact;

  customTrigger_ptr = map_customTrigger[config.trigger];
}
