/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "rigidBodyModel.hpp"

void RLS::RigidBodyModel::initialize(const int &uniqueNum, RigidBodyModelInfo &info, WorldModel &worldModel)
{
  if(debug) DEBUG;

  this->uniqueNum = uniqueNum;

  this->info = &info;
  this->worldModel = &worldModel;

  this->info->name = "default";

  resize();
}
