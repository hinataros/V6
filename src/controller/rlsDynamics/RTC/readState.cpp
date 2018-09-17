/**
   @author Sho Miyahara 2017
*/

#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::readState(RLS::TreeModel &hoap2)
{
  if(debug) DEBUG;

  if(m_basePosIn.isNew())
    m_basePosIn.read();
  if(m_baseVelIn.isNew())
    m_baseVelIn.read();
  if(m_angleIn.isNew())
    m_angleIn.read();
  if(m_angVelIn.isNew())
    m_angVelIn.read();
  if(m_eeForceIn.isNew())
    m_eeForceIn.read();

  for(int i=0; i<3; i++)
    hoap2.link[hoap2.info.rootNode].r(i) = m_basePos.data[i];

  for(int i=0, j=0, k=3; k<12; k++){
    hoap2.link[hoap2.info.rootNode].R(i,j) = m_basePos.data[k];
    if(j==2){
      i++;j=0;
    }else j++;
  }

  for(int i=0; i<3; i++){
    hoap2.link[hoap2.info.rootNode].v(i) = m_baseVel.data[i];
    hoap2.link[hoap2.info.rootNode].w(i) = m_baseVel.data[3+i];
  }

  hoap2.link[hoap2.info.rootNode].vo =
    hoap2.link[hoap2.info.rootNode].v - cross(hoap2.link[hoap2.info.rootNode].w)*hoap2.link[hoap2.info.rootNode].r;

  VectorXd th = VectorXd(m_angle.data.length());
  VectorXd dth = VectorXd(m_angle.data.length());
  for(unsigned i=0; i<m_angle.data.length(); i++)
    th(i) = m_angle.data[i];
  for(unsigned i=0; i<m_angVel.data.length(); i++)
    dth(i) = m_angVel.data[i];

  hoap2.writeJointStateVector("joint angle", th);
  hoap2.writeJointStateVector("joint velocity", dth);

  VectorXd FTsensor = VectorXd(m_eeForce.data.length());
  for(int i=0; i<m_eeForce.data.length(); i++)
    FTsensor(i) = m_eeForce.data[i];

  hoap2.writeSensorNodeValueVector("force torque sensor", FTsensor);
}
