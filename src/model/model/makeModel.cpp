/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "model.hpp"

void RLS::Model::makeModel(const string &path_yaml_model)
{
  if(debug) DEBUG;

  struct stat statFile;
  if(stat(path_yaml_model.c_str(), &statFile)!=0)
    cout << manip_error("WorldModel::readModel() error...") << endl
         << manip_error("no such file '"+path_yaml_model+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_model.c_str());

  if(doc["Tree model"][0])
    info.treeModelNum = doc["Tree model"].size();
  else if(doc["Tree model"])
    info.treeModelNum = 1;

  info.treeModel = new TreeModelInfo[info.treeModelNum];
  treeModel = new TreeModel[info.treeModelNum];

  if(doc["Rigid body model"][0])
    info.rigidBodyModelNum = doc["Rigid body model"].size();
  else if(doc["Rigid body model"])
    info.rigidBodyModelNum = 1;

  info.rigidBodyModel = new RigidBodyModelInfo[info.rigidBodyModelNum];
  rigidBodyModel = new RigidBodyModel[info.rigidBodyModelNum];
}
