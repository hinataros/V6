/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerModel.hpp"

void RLS::ControllerModel::initialize(Model &model)
{
  if(debug) DEBUG;

  setModel(model);

  treeModel = new ControllerTreeModel[model.info.treeModelNum];

  for(int i=0; i<model.info.treeModelNum; i++)
    treeModel[i].initialize(model.worldModel, model.info.treeModel[i], model.treeModel[i]);

  // initial update
  update();
}
