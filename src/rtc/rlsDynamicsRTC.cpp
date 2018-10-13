/**
   @author Sho Miyahara 2018
*/

#include "rlsDynamicsRTC.h"

RLS::Config config;
RLS::Model model;
RLS::RlsDynamics rlsDynamics;
RLS::Output output;

RLS::SharedMemory sharedMemory;
RLS::SharedData sharedData;

static const char* rlsDynamicsRTC_spec[] =
  {
    "implementation_id", "rlsDynamicsRTC",
    "type_name",         "rlsDynamicsRTC",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "RLS",
    "category",          "Generic",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };

RlsDynamicsRTC::RlsDynamicsRTC(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_angleIn("th", m_angle),
    m_angVelIn("dth", m_angVel),
    m_basePosIn("XB", m_basePos),
    m_baseVelIn("VB", m_baseVel),
    m_eeForceIn("F", m_eeForce),

    m_torqueOut("tau", m_torque),
    m_externalForceOut("Fext", m_externalForce)
{
}

RlsDynamicsRTC::~RlsDynamicsRTC()
{
}

RTC::ReturnCode_t RlsDynamicsRTC::onInitialize()
{
  cout << "RlsDynamicsRTC::onInitialize()" << endl;

  // Set InPort buffers
  addInPort("th", m_angleIn);
  addInPort("dth", m_angVelIn);
  addInPort("XB", m_basePosIn);
  addInPort("VB", m_baseVelIn);
  addInPort("F", m_eeForceIn);

  // Set OutPort buffer
  addOutPort("tau", m_torqueOut);
  addOutPort("Fext", m_externalForceOut);

  return RTC::RTC_OK;
}

RTC::ReturnCode_t RlsDynamicsRTC::onActivated(RTC::UniqueId ec_id)
{
  cout << "RlsDynamicsRTC::onActivate()" << endl << endl;

  t = 0.;
  controllerNum = 1;
  controllerID = 0;

  config.readConfig();
  model.initialize(config.dir.share, config.path_yaml.model);
  rlsDynamics.initialize(controllerID, config.path_yaml.controller, model);
  output.initialize(config.dir.link, config.path_yaml.output,
                    model.info, controllerNum, model.worldModel);

  // cout << "=========================================" << endl;
  // cout << "Body : "<< model.hoap2.info.name.body << ".body" << endl;
  // cout << "cnoid: "<< model.hoap2.info.name.cnoid << ".cnoid" << endl;
  // cout << "Work : "<< config.controller.name << ".work" << endl;
  // cout << "=========================================" << endl << endl;

  if(config.shm.flag)
    sharedMemory.initialize();

  // initialize torque size
  m_angleIn.read();
  m_torque.data.length(m_angle.data.length());
  for(size_t i=0; i<m_angle.data.length(); ++i)
    m_torque.data[i] = 0.;

  m_externalForce.data.length(6);
  for(size_t i=0; i<6; ++i)
    m_externalForce.data[i] = 0.;

  controlModelID = rlsDynamics.info.controlModelID;

  // smiyahara: 要検討
  setControlModelState(model.info.treeModel[controlModelID], model.treeModel[controlModelID]);

  // if(config.flag.shm){
  //   sharedMemory.getData(&sharedData);
  //   readSharedData(model.object, sharedData);
  // }

  model.update();
  tau = rlsDynamics.rlsDynamics(t);
  Fext = rlsDynamics.virtualInput;

  // if(config.shm.flag){
  //   writeSharedData(model.hoap2.tm_list, rlsDynamics.dc_list, sharedData);
  //   sharedMemory.putData(&sharedData);
  // }

  for(int i=0; i<model.info.treeModelNum; i++)
    output.treeModelList_temp[i] = model.treeModel[i].outputList;
  for(int i=0; i<controllerNum; i++)
    output.rlsDynamicsList_temp[i] = rlsDynamics.outputList;

  output.pushBack(t);

  writeInput();

  t += model.worldModel.dt;

  return RTC::RTC_OK;
}

RTC::ReturnCode_t RlsDynamicsRTC::onDeactivated(RTC::UniqueId ec_id)
{
  cout << "RlsDynamicsRTC::onDeactivated()" << endl;

  // smiyahara: 要検討
  model.worldModel.n = (t - model.worldModel.t0)/model.worldModel.dt;

  setControlModelState(model.info.treeModel[controlModelID], model.treeModel[controlModelID]);

  // if(config.flag.shm){
  //   sharedMemory.getData(&sharedData);
  //   readSharedData(model.object, sharedData);
  // }

  model.update();
  tau = rlsDynamics.rlsDynamics(t);
  Fext = rlsDynamics.virtualInput;

  // if(config.flag.shm){
  //   writeSharedData(model.hoap2.tm_list, rlsDynamics.dc_list, sharedData);
  //   sharedMemory.putData(&sharedData);
  // }

  for(int i=0; i<model.info.treeModelNum; i++)
    output.treeModelList_temp[i] = model.treeModel[i].outputList;
  for(int i=0; i<controllerNum; i++)
    output.rlsDynamicsList_temp[i] = rlsDynamics.outputList;

  output.pushBack(t);

  output.output();

  if(config.shm.flag)
    sharedMemory.finalize();

  output.finalize();
  rlsDynamics.finalize();
  model.finalize();

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RlsDynamicsRTC::onExecute(RTC::UniqueId ec_id)
{
  setControlModelState(model.info.treeModel[controlModelID], model.treeModel[controlModelID]);

  // if(config.flag.shm){
  //   sharedMemory.getData(&sharedData);
  //   readSharedData(model.object, sharedData);
  // }

  model.update();
  tau = rlsDynamics.rlsDynamics(t);
  Fext = rlsDynamics.virtualInput;

  // if(config.flag.shm){
  //   writeSharedData(model.hoap2.tm_list, rlsDynamics.dc_list, sharedData);
  //   sharedMemory.putData(&sharedData);
  // }

  for(int i=0; i<model.info.treeModelNum; i++)
    output.treeModelList_temp[i] = model.treeModel[i].outputList;
  for(int i=0; i<controllerNum; i++)
    output.rlsDynamicsList_temp[i] = rlsDynamics.outputList;

  output.pushBack(t);

  writeInput();

  t += model.worldModel.dt;

  return RTC::RTC_OK;
}

extern "C"
{
  void rlsDynamicsRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(rlsDynamicsRTC_spec);
    manager->registerFactory(profile,
                             RTC::Create<RlsDynamicsRTC>,
                             RTC::Delete<RlsDynamicsRTC>);
  }
};
