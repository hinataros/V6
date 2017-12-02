#include "objectRTC.h"

void ObjectRTC::readState(RLS::SharedData &sharedData)
{
  // if(config.flag.debug) DEBUG;

  if(m_objectPosIn.isNew())
    m_objectPosIn.read();
  if(m_objectVelIn.isNew())
    m_objectVelIn.read();

  for(int i=0; i<3; i++)
    sharedData.rR[i] = m_objectPos.data[i];

  for(int i=0; i<9; i++)
    sharedData.RR[i] = m_objectPos.data[3+i];

  for(int i=0; i<3; i++){
    sharedData.vR[i] = m_objectVel.data[i];
    sharedData.wR[i] = m_objectVel.data[3+i];
  }

  if(m_objectForceIn.isNew())
    m_objectForceIn.read();

  for(int i=0; i<3; i++){
    sharedData.fR[i] = m_objectForce.data[i];
    sharedData.nR[i] = m_objectForce.data[3+i];
  }
}
