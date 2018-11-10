/**
   @author Sho Miyahara 2018
*/

#include <unistd.h>
#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"

void RLS::Config::readInitYaml()
{
  if(debug) DEBUG;

  string path = dir.link + "yaml/_init_.yaml";

  struct stat statFile;
  if(stat(path.c_str(), &statFile)!=0)
    cout << manip_error("Config::readInitYaml() error...") << endl
         << manip_error("no such file '"+path+"'") << endl;

  string configKeyName = "config";
  YAML::Node doc = YAML::LoadFile(path.c_str());

  if(doc[configKeyName])
    _init_config = doc[configKeyName].as<string>();

  path_yaml.config = dir.link + "yaml/config/" + _init_config;
}
