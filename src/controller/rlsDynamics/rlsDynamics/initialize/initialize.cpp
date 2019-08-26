/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

void RLS::RlsDynamics::initialize(const int &controllerID, const string &path_yaml_controller, Model &model)
{
  if(debug) DEBUG;

  initializeExt();
  setDefaultConfig();

  yamlInfo.initialize(path_yaml_controller, controllerID);

  topState.doc = yamlInfo.docDist();
  seqNum = -1;
  stateScanner(topState);
  // statePrinter(topState); // amiyata
  // gc;
  yamlInfo.sequenceNum = seqNum+1;

  readControllerHeader();
  setModelInfo(model.info);

  controllerModel.initialize(model);
  this->worldModel = controllerModel.worldModel;
  this->model = &controllerModel.treeModel[this->info.controlModelID];

  constraintModel.initialize(this->info.model, *this->model);
  setConstraintInfo(constraintModel.info.constraint);

  des.initialize(*this->worldModel, this->info.model, *this->model, constraintModel, yamlInfo);
  fb.initialize(this->info.model, *this->model, yamlInfo, des);

  resize();
  setControllerMap();
  ext->initialize(this);

  // read controller file
  // ********************************
  yamlInfo.reset(); // amiyata default reset
  allReadController();

  initializeStateTrigger();

  localInitialize();
}
