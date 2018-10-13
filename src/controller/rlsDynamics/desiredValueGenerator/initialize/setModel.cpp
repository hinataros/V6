/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::setModel(const TreeModelInfo &info, const ControllerTreeModel &model)
{
  if(debug) DEBUG;

  this->info = &info;
  this->model = &model;
}
