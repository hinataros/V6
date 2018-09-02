/**
   @author Sho Miyahara 2017
*/

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readModel(string dir_model)
{
  if(debug) DEBUG;

  YAML::Node doc = YAML::LoadFile(dir_model.c_str());

  info.name.body = doc["Model"]["Body name"].as<string>();
  info.name.cnoid = doc["Model"]["cnoid name"].as<string>();

  info.controlNodeNum = doc["Model"]["Control node"].size();

  info.controlNode = new Contact[info.controlNodeNum];

  for(int i=0; i<info.controlNodeNum; i++)
    info.controlNode[i].name = doc["Model"]["Control node"][i].as<string>();
}
