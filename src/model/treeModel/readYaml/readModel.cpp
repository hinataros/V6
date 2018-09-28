/**
   @author Sho Miyahara 2017
*/

#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readModel(const string &dir_model)
{
  if(debug) DEBUG;

  struct stat statFile;
  if(stat(dir_model.c_str(), &statFile)!=0)
    cout << manip_error("TreeModel::readModel() error...") << endl
         << manip_error("no such file '"+dir_model+"'") << endl;

  YAML::Node doc = YAML::LoadFile(dir_model.c_str());

  info.dynamics_flag = doc["Model"]["Dynamics"].as<bool>();
  info.name.body = doc["Model"]["Body name"].as<string>();
  info.name.cnoid = doc["Model"]["cnoid name"].as<string>();

  info.controlNodeNum = doc["Model"]["Control node"].size();

  info.controlNode = new Contact[info.controlNodeNum];

  for(int i=0; i<info.controlNodeNum; i++)
    info.controlNode[i].name = doc["Model"]["Control node"][i].as<string>();
}
