/**
   @author Sho Miyahara 2018
*/

#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::writeInput()
{
  if(debug) DEBUG;

  for(unsigned i=0; i<m_angle.data.length(); i++)
    m_torque.data[i] = tau(i);

  // for(unsigned i=0; i<m_angle.data.length(); i++)
  //   o(m_torque.data[i]);

  for(int i=0; i<6; i++)
    m_externalForce.data[i] = Fext(i);

  // for(int i=0; i<6; i++)
  //   o(m_externalForce.data[i]);

  m_torqueOut.write();
  m_externalForceOut.write();
}
