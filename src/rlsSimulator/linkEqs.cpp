/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::linkEqs(Model &model, Controller &controller, Output &output)
{
  if(debug) DEBUG;

  setState2Model(model);

  model.update();

  for(int i=0; i<controller.controllerNum; i++)
    u[model.info.modelID[controller.rlsDynamics[i].info.controlModel.name]]
      = controller.rlsDynamics[i].rlsDynamics(t);

  for(int i=0; i<model.info.treeModelNum; i++)
    output.treeModelList_temp[i] = model.treeModel[i].outputList;
  for(int i=0; i<controller.controllerNum; i++)
    output.rlsDynamicsList_temp[i] = controller.rlsDynamics[i].outputList;

  output.pushBack(t);
}

void RLS::RlsSimulator::linkEqs(Model &model, Controller &controller)
{
  if(debug) DEBUG;

  model.update();

  for(int i=0; i<controller.controllerNum; i++)
    u[model.info.modelID[controller.rlsDynamics[i].info.controlModel.name]]
      = controller.rlsDynamics[i].rlsDynamics(t);
}
