/**
   @author Sho Miyahara 2017
*/

#include "objectRTC.h"

RLS::SharedMemory sharedMemory;
RLS::SharedData sharedData;

static const char* objectRTC_spec[] =
  {
    "implementation_id", "objectRTC",
    "type_name",         "objectRTC",
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

ObjectRTC::ObjectRTC(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_objectPosIn("XO", m_objectPos),
    m_objectVelIn("VO", m_objectVel),
    m_objectForceIn("FO", m_objectForce)
{
}

ObjectRTC::~ObjectRTC()
{
}

RTC::ReturnCode_t ObjectRTC::onInitialize()
{
  cout << "ObjectRTC::onInitialize()" << endl;

  // Set InPort buffers
  addInPort("XO", m_objectPosIn);
  addInPort("VO", m_objectVelIn);
  addInPort("FO", m_objectForceIn);

  return RTC::RTC_OK;
}

RTC::ReturnCode_t ObjectRTC::onActivated(RTC::UniqueId ec_id)
{
  cout << "ObjectRTC::onActivate()" << endl;

  sharedMemory.initialize();
  // object.initialize();

  // smiyahara: 要検討
  readState(sharedData);
  if(read)
    sharedMemory.putData(&sharedData);
  if(write)
    sharedMemory.getData(&sharedData);

  writeInput(sharedData);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t ObjectRTC::onDeactivated(RTC::UniqueId ec_id)
{
  cout << "ObjectRTC::onDeactivated()" << endl;

  readState(sharedData);
  if(read)
    sharedMemory.putData(&sharedData);
  if(write)
    sharedMemory.getData(&sharedData);

  writeInput(sharedData);

  sharedMemory.finalize();

  return RTC::RTC_OK;
}


RTC::ReturnCode_t ObjectRTC::onExecute(RTC::UniqueId ec_id)
{
  readState(sharedData);
  if(read)
    sharedMemory.putData(&sharedData);
  if(write)
    sharedMemory.getData(&sharedData);

  writeInput(sharedData);

  return RTC::RTC_OK;
}

extern "C"
{
  void objectRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(objectRTC_spec);
    manager->registerFactory(profile,
                             RTC::Create<ObjectRTC>,
                             RTC::Delete<ObjectRTC>);
  }
};
