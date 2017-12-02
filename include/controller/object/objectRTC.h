#ifndef OBJECTRTC_H
#define OBJECTRTC_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <iostream>

#include "sharedMemory.hpp"
#include "sharedData.hpp"

/* #include "model.hpp" */

// #include "object.hpp"

using namespace std;
using namespace RTC;

class ObjectRTC: public RTC::DataFlowComponentBase
{
public:
  ObjectRTC(RTC::Manager* manager);
  ~ObjectRTC();

   virtual RTC::ReturnCode_t onInitialize();
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

protected:
  RTC::TimedDoubleSeq m_objectPos;
  InPort<RTC::TimedDoubleSeq> m_objectPosIn;
  RTC::TimedDoubleSeq m_objectVel;
  InPort<RTC::TimedDoubleSeq> m_objectVelIn;
  RTC::TimedDoubleSeq m_objectForce;
  InPort<RTC::TimedDoubleSeq> m_objectForceIn;

private:
  void readState(RLS::SharedData&);
  // void writeInput(RLS::Config&);
};

extern "C"
{
  DLL_EXPORT void objectRTCInit(RTC::Manager* manager);
};

#endif // OBJECTRTC_H
