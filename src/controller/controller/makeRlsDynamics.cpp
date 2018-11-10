/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"

void RLS::Controller::makeRlsDynamics(const string &path_yaml_controller)
{
  if(debug) DEBUG;

  string controllerKeyName = "controller";

  struct stat statFile;
  if(stat(path_yaml_controller.c_str(), &statFile)!=0)
    cout << manip_error("Controller::makeController() error...") << endl
         << manip_error("no such file '"+path_yaml_controller+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_controller.c_str());

  if(doc[controllerKeyName][0])
    controllerNum = doc[controllerKeyName].size();
  else if(doc[controllerKeyName])
    controllerNum = 1;

  rlsDynamics = new RlsDynamics[controllerNum];
}
