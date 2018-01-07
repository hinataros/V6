/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::resize(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  for(int i=1; i<info.value.node; i++)
    cal_X.segment(6*(i-1), 6) <<
      model.hoap2.limb[i].node[info.limb[i].dof].r,
      R2xi(model.hoap2.limb[i].node[info.limb[i].dof].R);

  for(int i=1; i<info.value.node; i++)
    cal_V.segment(6*(i-1), 6) <<
      model.hoap2.limb[i].node[info.limb[i].dof].v,
      model.hoap2.limb[i].node[info.limb[i].dof].w;

  for(int i=1; i<info.value.node; i++)
    cal_F.segment(6*(i-1), 6) <<
      model.hoap2.limb[i].node[info.limb[i].dof].f,
      model.hoap2.limb[i].node[info.limb[i].dof].n;

  for(int i=1, temp=0; i<info.value.node; temp += info.limb[i].dof, i++)
    cal_J.block(6*(i-1),temp,6,info.limb[i].dof) = model.hoap2.limb[i].J;

  for(int i=1; i<info.value.node; i++)
    bb_Rk.block(6*(i-1),6*(i-1),3,3) =
      bb_Rk.block(6*(i-1)+3,6*(i-1)+3,3,3) = Matrix3d::Identity();

  for(int i=1; i<info.value.node; i++){
    TB2k.block(6*(i-1),0,6,6) = Matrix6d::Identity();
    TB2k.block(6*(i-1),3,3,3) =
      -cross(model.hoap2.limb[i].node[info.limb[i].dof].r - model.hoap2.limb[0].node[0].r);
  }

  for(int i=1; i<info.value.node; i++){
    TC2k.block(6*(i-1),0,6,6) = Matrix6d::Identity();
    TC2k.block(6*(i-1),3,3,3) =
      -cross(model.hoap2.limb[i].node[info.limb[i].dof].r - model.hoap2.all.rC);
  }

  // diff
  for(int i=1, temp=0; i<info.value.node; temp += info.limb[i].dof, i++)
    cal_dJ.block(6*(i-1),temp,6,info.limb[i].dof) = model.hoap2.limb[i].dJ;

  for(int i=1; i<info.value.node; i++)
    bb_dRk.block(6*(i-1),6*(i-1),3,3) = bb_dRk.block(6*(i-1)+3,6*(i-1)+3,3,3)
      = cross(model.hoap2.limb[i].node[info.limb[i].dof].w)*model.hoap2.limb[i].node[info.limb[i].dof].R;

  for(int i=1; i<info.value.node; i++)
    dTB2k.block(6*(i-1),3,3,3) =
      -cross(model.hoap2.limb[i].node[info.limb[i].dof].v - model.hoap2.limb[0].node[0].v);

  for(int i=1; i<info.value.node; i++)
    dTC2k.block(6*(i-1),3,3,3) =
      -cross(model.hoap2.limb[i].node[info.limb[i].dof].v - model.hoap2.all.vC);
}
