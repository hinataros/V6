#include "rlsDynamicsRTC.h"

RLS::Config config;
RLS::Info info;
RLS::Model model;
RLS::RlsDynamics rlsDynamics;
RLS::Output output;

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
    m_basePosIn("rB", m_basePos),
    m_baseVelIn("vB", m_baseVel),
    m_rightFootForceIn("FFr", m_rightFootForce),
    m_leftFootForceIn("FFl", m_leftFootForce),

    m_torqueOut("tau", m_torque)
{
}

RlsDynamicsRTC::~RlsDynamicsRTC()
{
}

RTC::ReturnCode_t RlsDynamicsRTC::onInitialize()
{
  cout << "RTC::onInitialize()" << endl;

  // Set InPort buffers
  addInPort("th", m_angleIn);
  addInPort("dth", m_angVelIn);
  addInPort("rB", m_basePosIn);
  addInPort("vB", m_baseVelIn);

  addInPort("FFr", m_rightFootForceIn);
  addInPort("FFl", m_leftFootForceIn);

  // Set OutPort buffer
  addOutPort("tau", m_torqueOut);

  return RTC::RTC_OK;
}

RTC::ReturnCode_t RlsDynamicsRTC::onActivated(RTC::UniqueId ec_id)
{
  cout << "RTC::onActivate()" << endl;

  t = 0.;

  config.readConfig();
  info.initialize(config);
  model.readModel(config, info);
  rlsDynamics.initialize(config, info);

  // initialize torque size
  m_angleIn.read();
  m_torque.data.length(m_angle.data.length());
  for(size_t i=0; i<m_angle.data.length(); ++i)
    m_torque.data[i] = 0.;

  // smiyahara: 要検討
  readState(config, info, model);

  tau = rlsDynamics.rlsDynamics(config, info, model, t);

  output.tm_temp = model.tm_list;
  output.dc_temp = rlsDynamics.dc_list;

  writeInput(config);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RlsDynamicsRTC::onDeactivated(RTC::UniqueId ec_id)
{
  cout << "RTC::onDeactivated()" << endl;

  // smiyahara: はい?
  info.sim.n = (t - info.sim.t0) / info.sim.dt;

  readState(config, info, model);

  tau = rlsDynamics.rlsDynamics(config, info, model, t);

  output.dc_temp = rlsDynamics.dc_list;
  output.tm_temp = model.tm_list;
  output.pushBack(config, t);

  output.output(config, info);
  output.finalize(config);

  model.deleteModel(config, info);
  info.finalize(config);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RlsDynamicsRTC::onExecute(RTC::UniqueId ec_id)
{
  readState(config, info, model);

  tau = rlsDynamics.rlsDynamics(config, info, model, t);

  output.dc_temp = rlsDynamics.dc_list;
  output.tm_temp = model.tm_list;
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


