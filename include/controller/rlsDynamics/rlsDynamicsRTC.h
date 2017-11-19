#ifndef RLSDYNAMICSRTC_H
#define RLSDYNAMICSRTC_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"

using namespace RTC;

class RlsDynamicsRTC: public RTC::DataFlowComponentBase
{
public:
  RlsDynamicsRTC(RTC::Manager* manager);
  ~RlsDynamicsRTC();

   virtual RTC::ReturnCode_t onInitialize();
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

protected:
  RTC::TimedDoubleSeq m_angle;
  InPort<RTC::TimedDoubleSeq> m_angleIn;
  RTC::TimedDoubleSeq m_angVel;
  InPort<RTC::TimedDoubleSeq> m_angVelIn;
  RTC::TimedDoubleSeq m_basePos;
  InPort<RTC::TimedDoubleSeq> m_basePosIn;
  RTC::TimedDoubleSeq m_baseVel;
  InPort<RTC::TimedDoubleSeq> m_baseVelIn;

  RTC::TimedDoubleSeq m_rightFootForce;
  InPort<RTC::TimedDoubleSeq> m_rightFootForceIn;
  RTC::TimedDoubleSeq m_leftFootForce;
  InPort<RTC::TimedDoubleSeq> m_leftFootForceIn;

  RTC::TimedDoubleSeq m_torque;
  OutPort<RTC::TimedDoubleSeq> m_torqueOut;

private:
  Matrix3d cross(Vector3d x)
  {
    Matrix3d a = Matrix3d::Zero();

    a <<
      0    ,-x(2), x(1),
      x(2) ,    0,-x(0),
      -x(1), x(0),    0;

    return a;
  }
  double t;
  VectorXd tau;

  void readState(RLS::Config&, RLS::Info &info, RLS::Model &model);
  void writeInput(RLS::Config&);
};

extern "C"
{
  DLL_EXPORT void rlsDynamicsRTCInit(RTC::Manager* manager);
};

#endif // RLSDYNAMICSRTC_H