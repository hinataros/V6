/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::setModel(TreeModelInfo &info, const ControllerTreeModel &model)
{
  if(debug) DEBUG;

  this->info.model = &info;
  this->model = &model;
}
