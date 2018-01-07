/**
   @author Sho Miyahara 2017
*/

#include "rlsDynamicsRTC.h"

RLS::Config config;
RLS::Info info;
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
    m_rightFootForceIn("FFr", m_rightFootForce),
    m_leftFootForceIn("FFl", m_leftFootForce),

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

  addInPort("FFr", m_rightFootForceIn);
  addInPort("FFl", m_leftFootForceIn);

  // Set OutPort buffer
  addOutPort("tau", m_torqueOut);

  addOutPort("Fext", m_externalForceOut);

  return RTC::RTC_OK;
}

RTC::ReturnCode_t RlsDynamicsRTC::onActivated(RTC::UniqueId ec_id)
{
  cout << "RlsDynamicsRTC::onActivate()" << endl;

  t = 0.;

  config.readConfig();
  info.initialize(config);
  model.readModel(config, info);
  rlsDynamics.initialize(config, info);

  if(config.flag.shm)
    sharedMemory.initialize();

  // initialize torque size
  m_angleIn.read();
  m_torque.data.length(m_angle.data.length());
  for(size_t i=0; i<m_angle.data.length(); ++i)
    m_torque.data[i] = 0.;

  m_externalForce.data.length(6);
  for(size_t i=0; i<6; ++i)
    m_externalForce.data[i] = 0.;

  // smiyahara: 要検討
  readState(config, info, model.hoap2);

  if(config.flag.shm){
    sharedMemory.getData(&sharedData);
    readSharedData(config, info, model.object, sharedData);
  }

  tau = rlsDynamics.rlsDynamics(config, info, model, t);
  Fext = rlsDynamics.virtualInput;

  output.tm_temp = model.hoap2.tm_list;
  output.dc_temp = rlsDynamics.dc_list;

  writeInput(config);

  return RTC::RTC_OK;
}

RTC::ReturnCode_t RlsDynamicsRTC::onDeactivated(RTC::UniqueId ec_id)
{
  cout << "RlsDynamicsRTC::onDeactivated()" << endl;

  // smiyahara: はい?
  info.sim.n = (t - info.sim.t0) / info.sim.dt;

  readState(config, info, model.hoap2);

  if(config.flag.shm){
    sharedMemory.getData(&sharedData);
    readSharedData(config, info, model.object, sharedData);
  }

  tau = rlsDynamics.rlsDynamics(config, info, model, t);
  Fext = rlsDynamics.virtualInput;

  output.dc_temp = rlsDynamics.dc_list;
  output.tm_temp = model.hoap2.tm_list;
  output.pushBack(config, t);

  if(config.flag.shm)
    sharedMemory.finalize();

  output.output(config, info);
  output.finalize(config);

  model.deleteModel(config, info);
  info.finalize(config);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RlsDynamicsRTC::onExecute(RTC::UniqueId ec_id)
{
  readState(config, info, model.hoap2);

  if(config.flag.shm){
    sharedMemory.getData(&sharedData);
    readSharedData(config, info, model.object, sharedData);
  }

  tau = rlsDynamics.rlsDynamics(config, info, model, t);
  Fext = rlsDynamics.virtualInput;

  output.dc_temp = rlsDynamics.dc_list;
  output.tm_temp = model.hoap2.tm_list;
  output.pushBack(config, t);

  writeInput(config);

  t += info.sim.dt;

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
