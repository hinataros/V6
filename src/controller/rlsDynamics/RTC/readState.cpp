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

  for(int i=0; i<3; i++)
    hoap2.limb[0].node[0].r(i) = m_basePos.data[i];

  for(int i=0, j=0, k=3; k<12; k++){
    hoap2.limb[0].node[0].R(i,j) = m_basePos.data[k];
    if(j==2){
      i++;
      j=0;
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

  // smiyahara: 他にいい方法があるかも
  if(config.model.name=="skeleton"||
     config.model.name=="skeletonA7"){
    if(m_rightFootForceIn.isNew())
      m_rightFootForceIn.read();
    if(m_leftFootForceIn.isNew())
      m_leftFootForceIn.read();

    for(int i=0; i<3; i++){
      hoap2.limb[1].node[info.limb[1].dof].f(i) = m_rightFootForce.data[i];
      hoap2.limb[1].node[info.limb[1].dof].n(i) = m_rightFootForce.data[i+3];
      hoap2.limb[2].node[info.limb[2].dof].f(i) = m_leftFootForce.data[i];
      hoap2.limb[2].node[info.limb[2].dof].n(i) = m_leftFootForce.data[i+3];
    }

    // choreonoid: [z, -y, x]^T
    Matrix3d Rf = Matrix3d::Identity();
    Rf <<
      0., 0.,1.,
      0.,-1.,0.,
      1., 0.,0.;

    hoap2.limb[1].node[info.limb[1].dof].f = Rf*hoap2.limb[1].node[info.limb[1].dof].f;
    hoap2.limb[1].node[info.limb[1].dof].n = Rf*hoap2.limb[1].node[info.limb[1].dof].n;
    hoap2.limb[2].node[info.limb[2].dof].f = Rf*hoap2.limb[2].node[info.limb[2].dof].f;
    hoap2.limb[2].node[info.limb[2].dof].n = Rf*hoap2.limb[2].node[info.limb[2].dof].n;
  }
}
