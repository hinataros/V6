/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readControllerHeader()
{
  if(debug) DEBUG;

  string controlModelKeyName = "control model";
  string inputKeyName = "input";
  string drivenKeyName = "driven";
  string triggerKeyName = "trigger";

  string extTriggerKeyName = "ext trigger";

  if(yamlInfo.doc.controllerKey[controlModelKeyName])
    config.controlModel = yamlInfo.doc.controllerKey[controlModelKeyName].as<string>();

  if(yamlInfo.doc.controllerKey[inputKeyName])
    config.input = yamlInfo.doc.controllerKey[inputKeyName].as<string>();

  if(yamlInfo.doc.controllerKey[drivenKeyName])
    config.driven = yamlInfo.doc.controllerKey[drivenKeyName].as<string>();

  if(config.driven=="event"||config.driven=="mix"){
    if(yamlInfo.doc.controllerKey[extTriggerKeyName])
      extStateTrigger = yamlInfo.doc.controllerKey[extTriggerKeyName].as<bool>();
    if(yamlInfo.doc.controllerKey[triggerKeyName])
      config.trigger = yamlInfo.doc.controllerKey[triggerKeyName].as<string>();
  }
}
