/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readWorkHeader()
{
  if(yamlInfo.doc.controllerKey["Control model"])
    config.controlModel = yamlInfo.doc.controllerKey["Control model"].as<string>();

  if(yamlInfo.doc.controllerKey["Input"])
    config.input = yamlInfo.doc.controllerKey["Input"].as<string>();

  if(yamlInfo.doc.controllerKey["Driven"])
    config.driven = yamlInfo.doc.controllerKey["Driven"].as<string>();

  if(config.driven=="event"||config.driven=="mix")
    if(yamlInfo.doc.controllerKey["Trigger"])
      config.trigger = yamlInfo.doc.controllerKey["Trigger"].as<string>();
}
