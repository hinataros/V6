/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::initialize(const string &dir_share, const string &path_yaml_model)
{
  if(debug) DEBUG;

  initializeInfo();
  makeModel(path_yaml_model);

  worldModel.initialize(dir_share);
  for(int i=0; i<info.treeModelNum; i++)
    treeModel[i].initialize(i, info.treeModel[i], worldModel);
  for(int i=0; i<info.rigidBodyModelNum; i++)
    rigidBodyModel[i].initialize(i, info.rigidBodyModel[i], worldModel);

  worldModel.readModel(path_yaml_model);
  for(int i=0; i<info.treeModelNum; i++)
    treeModel[i].readModel(dir_share, path_yaml_model);
  for(int i=0; i<info.rigidBodyModelNum; i++)
    rigidBodyModel[i].readModel(dir_share, path_yaml_model);

  setID();

  initialUpdate();
}
