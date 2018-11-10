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

  string treeModelKeyName = "tree model";
  string rigidBodyModelKeyName = "rigid body model";

  struct stat statFile;
  if(stat(path_yaml_model.c_str(), &statFile)!=0)
    cout << manip_error("WorldModel::readModel() error...") << endl
         << manip_error("no such file '"+path_yaml_model+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_model.c_str());

  if(doc[treeModelKeyName][0])
    info.treeModelNum = doc[treeModelKeyName].size();
  else if(doc[treeModelKeyName])
    info.treeModelNum = 1;

  info.treeModel = new TreeModelInfo[info.treeModelNum];
  treeModel = new TreeModel[info.treeModelNum];

  if(doc[rigidBodyModelKeyName][0])
    info.rigidBodyModelNum = doc[rigidBodyModelKeyName].size();
  else if(doc[rigidBodyModelKeyName])
    info.rigidBodyModelNum = 1;

  info.rigidBodyModel = new RigidBodyModelInfo[info.rigidBodyModelNum];
  rigidBodyModel = new RigidBodyModel[info.rigidBodyModelNum];
}
