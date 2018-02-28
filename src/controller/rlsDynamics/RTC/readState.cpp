/**
   @author Sho Miyahara 2017
*/

#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::readState(RLS::Config &config, RLS::Info &info, RLS::TreeModel &hoap2)
{
  if(config.flag.debug) DEBUG;

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
    hoap2.limb[0].node[0].r(i) = m_basePos.data[i];

  for(int i=0, j=0, k=3; k<12; k++){
    hoap2.limb[0].node[0].R(i,j) = m_basePos.data[k];
    if(j==2){
      i++;j=0;
    }else j++;
  }

  for(int i=0; i<3; i++){
    hoap2.limb[0].node[0].v(i) = m_baseVel.data[i];
    hoap2.limb[0].node[0].w(i) = m_baseVel.data[3+i];
  }

  hoap2.limb[0].node[0].vo = hoap2.limb[0].node[0].v - cross(hoap2.limb[0].node[0].w)*hoap2.limb[0].node[0].r;

  for(unsigned i=0; i<m_angle.data.length(); i++)
    hoap2.all.th(i) = m_angle.data[i];
  for(unsigned i=0; i<m_angVel.data.length(); i++)
    hoap2.all.dth(i) = m_angVel.data[i];

  for(int i=1; i<info.value.node; i++)
    for(int j=0; j<3; j++){
      hoap2.limb[i].node[info.limb[i].dof].f(j) = m_eeForce.data[6*(i-1)+j];
      hoap2.limb[i].node[info.limb[i].dof].n(j) = m_eeForce.data[6*(i-1)+j+3];
    }
}
