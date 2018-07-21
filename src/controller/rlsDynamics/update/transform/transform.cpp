/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::transform(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  for(int i=1, temp=0; i<info.value.node; temp += info.limb[i].dof, i++){
    // cal_J.block(6*(i-1),temp,6,info.limb[i].dof) = jacobian(config, info, model.hoap2, i);
    // cal_dJ.block(6*(i-1),temp,6,info.limb[i].dof) = diffJacobian(config, info, model.hoap2, i);
    cal_J.block(6*(i-1),temp,6,info.limb[i].dof) = jacobian(config, info, model.hoap2, i, rkk[i-1]);
    cal_dJ.block(6*(i-1),temp,6,info.limb[i].dof) = diffJacobian(config, info, model.hoap2, i, rkk[i-1]);
  }

  for(int i=1; i<info.value.node; i++){
    Vector3d eePos = model.hoap2.limb[i].node[info.limb[i].dof].r + model.hoap2.limb[i].node[info.limb[i].dof].R*rkk[i-1];
    Vector3d eeVel = model.hoap2.limb[i].node[info.limb[i].dof].v + w2dR(model.hoap2.limb[i].node[info.limb[i].dof].w, model.hoap2.limb[i].node[info.limb[i].dof].R)*rkk[i-1];

    TB2k.block(6*(i-1),0,6,6) = spatialTransform(config, info, eePos - model.hoap2.limb[0].node[0].r);
    dTB2k.block(6*(i-1),0,6,6) = diffSpatialTransform(config, info, eeVel - model.hoap2.limb[0].node[0].v);

    TC2k.block(6*(i-1),0,6,6) = spatialTransform(config, info, eePos - model.hoap2.all.rC);
    dTC2k.block(6*(i-1),0,6,6) = diffSpatialTransform(config, info, eeVel - model.hoap2.all.vC);
  }
}
