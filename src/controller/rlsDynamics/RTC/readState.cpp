#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::readState(RLS::Config &config, RLS::Model &model)
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

  for(int i=0; i<3; i++)
    model.limb[0].node[0].r(i) = m_basePos.data[i];

  for(int i=0, j=0, k=3; k<12; k++){
    model.limb[0].node[0].R(i,j) = m_basePos.data[k];
    if(j==2){
      i++;
      j=0;
    }else j++;
  }

  for(int i=0; i<3; i++){
    model.limb[0].node[0].v(i) = m_baseVel.data[i];
    model.limb[0].node[0].w(i) = m_baseVel.data[3+i];
  }

  for(unsigned i=0; i<m_angle.data.length(); i++)
    model.all.th(i) = m_angle.data[i];
  for(unsigned i=0; i<m_angVel.data.length(); i++)
    model.all.dth(i) = m_angVel.data[i];
}
