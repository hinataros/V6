/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::setModel(const WorldModel &worldModel, const TreeModelInfo &info, TreeModel &model)
{
  if(debug) DEBUG;

  this->worldModel = &worldModel;

  this->info = &info;

  this->model = &model;
}
