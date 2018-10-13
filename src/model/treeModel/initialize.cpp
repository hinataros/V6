/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::initialize(const int &uniqueNum, TreeModelInfo &info, WorldModel &worldModel)
{
  if(debug) DEBUG;

  this->uniqueNum = uniqueNum;

  this->info = &info;
  this->worldModel = &worldModel;

  this->info->rootNode = 0;
  this->info->linkNum = 0;
  this->info->controlNodeNum = 0;
  this->info->sensorNodeNum = 0;

  this->info->dof.all = 0;
  this->info->dof.root = 0;
  this->info->dof.joint = 0;
}

