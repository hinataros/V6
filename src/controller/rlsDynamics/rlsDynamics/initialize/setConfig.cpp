/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::setConfig(const string &path_yaml_controller)
{
  if(debug) DEBUG;

  config.path_yaml_controller = path_yaml_controller;

  config.controlModel = "default";
  config.controlNodeNum = 0;

  config.input = "no input";
  config.driven = "flow";
  config.trigger = "default";
}
