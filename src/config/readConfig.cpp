/**
   @author Sho Miyahara 2018
*/

#include <unistd.h>
#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"

void RLS::Config::readConfig()
{
  if(debug) DEBUG;

  string executionKeyName = "execution";
  string modelKeyName = "model";
  string controllerKeyName = "controller";
  string outputKeyName = "output";
  string rlsSimulatorKeyName = "rlsSimulator";

  cout << "config: " << _init_config << endl;

  struct stat statFile;
  if(stat(path_yaml.config.c_str(), &statFile)!=0)
    cout << manip_error("Config::readConfig() error...") << endl
         << manip_error("no such file '"+path_yaml.config+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml.config.c_str());

  // execution config
  if(doc[executionKeyName]){
    if(doc[executionKeyName]["shared memory"])
      shm.flag = doc[executionKeyName]["shared memory"].as<bool>();

    if(option!="-d")
      if(doc[executionKeyName]["debug mode"])
        debug = doc[executionKeyName]["debug mode"].as<bool>();
  }

  // model config
  if(doc[modelKeyName])
    read.model = doc[modelKeyName].as<string>();
  else
    cout << manip_error("Config::readConfig() error...") << endl
         << manip_error("no model file") << endl;

  // controller config
  if(doc[controllerKeyName])
    read.controller = doc[controllerKeyName].as<string>();
  else
    cout << manip_error("Config::readConfig() error...") << endl
         << manip_error("no controller file") << endl;

  // output config
  if(doc[outputKeyName])
    read.output = doc[outputKeyName].as<string>();
  else
    cout << manip_error("Config::readConfig() error...") << endl
         << manip_error("no output file") << endl;

  // rlsSimulator config
  if(doc[rlsSimulatorKeyName])
    read.rlsSimulator = doc[rlsSimulatorKeyName].as<string>();
  else
    cout << manip_warning("Config::readConfig(): warning: ")
         << manip_warning("no rlsSimulator file") << endl;

  setPath();
}
