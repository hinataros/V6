/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::initialize(const WorldModel &worldModel, const TreeModelInfo &info, TreeModel &model)
{
  if(debug) DEBUG;

  setModel(worldModel, info, model);

  resize();

  setInitialValue();
}
