/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initialize(const int &controllerID, const string &path_yaml_controller, Model &model)
{
  if(debug) DEBUG;

  setConfig(path_yaml_controller);
  analysisYaml(controllerID);

  readWorkHeader();
  setModelInfo(model.info);

  controllerModel.initialize(model);
  this->worldModel = controllerModel.worldModel;
  this->model = &controllerModel.treeModel[this->info.controlModelID];

  des.initialize(this->info.model, *this->model, yamlInfo);
  fb.initialize(this->info.model, *this->model, yamlInfo, des);

  initializeConstraintInfo();

  resize();
  setControllerMap();

  // read controller file
  // ********************************
  yamlInfo.initialize("Default", 0, 0);

  des.readController();
  fb.readController();
  readController();
  // ********************************

  initializeStateTrigger();

  localInitialize();
}
