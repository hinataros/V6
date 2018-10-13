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

  cout << "config: " << _init_config << endl;

  struct stat statFile;
  if(stat(path_yaml.config.c_str(), &statFile)!=0)
    cout << manip_error("Config::readConfig() error...") << endl
         << manip_error("no such file '"+path_yaml.config+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml.config.c_str());

  // execution config
  if(doc["Execution"]){
    if(doc["Execution"]["Shared memory"])
      shm.flag = doc["Execution"]["Shared memory"].as<bool>();

    if(option!="-d")
      if(doc["Execution"]["Debug mode"])
        debug = doc["Execution"]["Debug mode"].as<bool>();
  }

  // model config
  if(doc["Model"])
    read.model = doc["Model"].as<string>();
  else
    cout << manip_error("Config::readConfig() error...") << endl
         << manip_error("no model file") << endl;

  // controller config
  if(doc["Controller"])
    read.controller = doc["Controller"].as<string>();
  else
    cout << manip_error("Config::readConfig() error...") << endl
         << manip_error("no controller file") << endl;

  // output config
  if(doc["Output"])
    read.output = doc["Output"].as<string>();
  else
    cout << manip_error("Config::readConfig() error...") << endl
         << manip_error("no output file") << endl;

  // rlsSimulator config
  if(doc["RlsSimulator"])
    read.rlsSimulator = doc["RlsSimulator"].as<string>();
  else
    cout << manip_warning("Config::readConfig(): warning: ")
         << manip_warning("no rlsSimulator file") << endl;

  setPath();
}
