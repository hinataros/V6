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

  for(int i=1; i<info.value.node; i++){
    cal_X.segment(6*(i-1), 6) <<
      model.hoap2.limb[i].node[info.limb[i].dof].r,
      R2xi(model.hoap2.limb[i].node[info.limb[i].dof].R);

    cal_V.segment(6*(i-1), 6) <<
      model.hoap2.limb[i].node[info.limb[i].dof].v,
      model.hoap2.limb[i].node[info.limb[i].dof].w;

    cal_F.segment(6*(i-1), 6) <<
      model.hoap2.limb[i].node[info.limb[i].dof].f,
      model.hoap2.limb[i].node[info.limb[i].dof].n;

    bb_Rk.block(6*(i-1),6*(i-1),3,3) =
      bb_Rk.block(6*(i-1)+3,6*(i-1)+3,3,3) = Matrix3d::Identity();

    bb_dRk.block(6*(i-1),6*(i-1),3,3) = bb_dRk.block(6*(i-1)+3,6*(i-1)+3,3,3)
      = cross(model.hoap2.limb[i].node[info.limb[i].dof].w)*model.hoap2.limb[i].node[info.limb[i].dof].R;
  }
}
