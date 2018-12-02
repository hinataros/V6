/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::setModel(const WorldModel &worldModel, const TreeModelInfo &info, const ControllerTreeModel &model, ConstraintModel &constraintModel)
{
  if(debug) DEBUG;

  this->worldModel = &worldModel;

  this->info = &info;
  this->model = &model;

  this->constraintModel = &constraintModel;
}
