/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::readRlsSimulator(const string &path_yaml_rlsSimulator, const Info &info)
{
  if(debug) DEBUG;

  struct stat statFile;
  if(stat(path_yaml_rlsSimulator.c_str(), &statFile)!=0)
    cout << manip_error("RlsSimulator::readRlsSimulator() error...") << endl
         << manip_error("no such file '"+path_yaml_rlsSimulator+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_rlsSimulator.c_str());

  if(doc["config"][0]){
    if(info.treeModelNum==doc["config"].size()){
      for(int i=0; i<info.treeModelNum; i++)
        this->config.controlInput[i] = doc["config"][i]["control input"].as<string>();
    }
    else{
      cout << manip_error("RlsSimulator::readRlsSimulator() error...") << endl
           << manip_error("does not match model number") << endl;
    }
  }
  else if(doc["config"]){
    for(int i=0; i<info.treeModelNum; i++)
      this->config.controlInput[i] = doc["config"]["control input"].as<string>();
  }
}
