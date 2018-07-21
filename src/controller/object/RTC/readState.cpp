/**
   @author Sho Miyahara 2017
*/

#include "objectRTC.h"

void ObjectRTC::readState(RLS::SharedData &sharedData)
{
  // if(config.flag.debug) DEBUG;

  if(m_objectPosIn.isNew())
    m_objectPosIn.read();
  if(m_objectVelIn.isNew())
    m_objectVelIn.read();

  for(int i=0; i<3; i++)
    sharedData.root.r[i] = m_objectPos.data[i];

  for(int i=0; i<9; i++)
    sharedData.root.R[i] = m_objectPos.data[3+i];

  for(int i=0; i<3; i++){
    sharedData.root.v[i] = m_objectVel.data[i];
    sharedData.root.w[i] = m_objectVel.data[3+i];
  }

  if(m_objectForceIn.isNew())
    m_objectForceIn.read();

  for(int i=0; i<3; i++){
    sharedData.root.f[i] = m_objectForce.data[i];
    sharedData.root.n[i] = m_objectForce.data[3+i];
  }
}
