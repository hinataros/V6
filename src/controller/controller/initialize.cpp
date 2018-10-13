/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"

void RLS::Controller::initialize(const string &path_yaml_controller, Model &model)
{
  if(debug) DEBUG;

  makeRlsDynamics(path_yaml_controller);

  for(int i=0; i<controllerNum; i++)
    rlsDynamics[i].initialize(i, path_yaml_controller, model);
}
