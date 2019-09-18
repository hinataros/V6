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
  seqNum = 0;
  stNum = 0;
  stateScanner(topState);
  if(monitor){
    statePrinter(topState); // amiyata
    // gc;
  }
  yamlInfo.sequenceNum = seqNum;

  readControllerHeader();
  setModelInfo(model.info);

  controllerModel.initialize(model);
  this->worldModel = controllerModel.worldModel;
  this->model = &controllerModel.treeModel[this->info.controlModelID];

  // amiyata 足の形保存 やり方もやる場所も微妙
  extractor.soleConvex = new vector<Vector2d>[info.model.controlNodeNum];
  for(int i=0; i<info.model.controlNodeNum; i++){
    if(this->model->model->link[info.model.controlNode[i].num].eeSize.rows()){
      for(int j=0; j<this->model->model->link[info.model.controlNode[i].num].eeSize.rows(); j++)
        extractor.soleConvex[i].push_back(this->model->model->link[info.model.controlNode[i].num].eeSize.row(j));
    }
  }

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
