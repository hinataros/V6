/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerModel.hpp"

void RLS::ControllerModel::setModel(const Model &model)
{
  if(debug) DEBUG;

  this->worldModel = &model.worldModel;

  this->info = &model.info;
}
