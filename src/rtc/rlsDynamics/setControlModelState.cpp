/**
   @author Sho Miyahara 2018
*/

#include "rlsDynamicsRTC.h"

Matrix3d cross(Vector3d x)
{
  Matrix3d a = Matrix3d::Zero();
  a <<
    0    ,-x(2), x(1),
    x(2) ,    0,-x(0),
    -x(1), x(0),    0;

  return a;
}

void RlsDynamicsRTC::setControlModelState(RLS::TreeModelInfo &info, RLS::TreeModel &model)
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
    model.link[info.rootNode].r(i) = m_basePos.data[i];

  for(int i=0, j=0, k=3; k<12; k++){
    model.link[info.rootNode].R(i,j) = m_basePos.data[k];
    if(j==2){
      i++;j=0;
    }else j++;
  }

  for(int i=0; i<3; i++){
    model.link[info.rootNode].v(i) = m_baseVel.data[i];
    model.link[info.rootNode].w(i) = m_baseVel.data[3+i];
  }

  model.link[info.rootNode].vo =
    model.link[info.rootNode].v - cross(model.link[info.rootNode].w)*model.link[info.rootNode].r;

  VectorXd th = VectorXd(m_angle.data.length());
  VectorXd dth = VectorXd(m_angle.data.length());
  for(unsigned i=0; i<m_angle.data.length(); i++)
    th(i) = m_angle.data[i];
  for(unsigned i=0; i<m_angVel.data.length(); i++)
    dth(i) = m_angVel.data[i];

  model.writeJointState("joint angle", th);
  model.writeJointState("joint velocity", dth);

  VectorXd FTsensor = VectorXd(m_eeForce.data.length());
  for(int i=0; i<m_eeForce.data.length(); i++)
    FTsensor(i) = m_eeForce.data[i];

  model.writeSensorNodeValue("force torque sensor", FTsensor);
}
