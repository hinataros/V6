#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::writeInput(RLS::Config &config)
{
  if(config.flag.debug) DEBUG;

  for(unsigned i=0; i<m_angle.data.length(); i++)
    m_torque.data[i] = tau(i);

  // for(unsigned i=0; i<m_angle.data.length(); i++)
  //   o(m_torque.data[i]);

  m_torqueOut.write();
}
