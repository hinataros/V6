/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::diffJacobian(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  Vector3d eePos = Vector3d::Zero();
  Vector3d eeVel = Vector3d::Zero();

  for(int i=1; i<info.value.node; i++){
    eePos = limb[i].node[info.limb[i].dof].r;
    eeVel = limb[i].node[info.limb[i].dof].v;

    for(int j=0; j<info.limb[i].dof; j++)
      limb[i].dJ.col(j) <<
	cross(limb[i].node[j].dsw)*(eePos - limb[i].node[j].r) + cross(limb[i].node[j].sw)*(eeVel - limb[i].node[j].v),
	limb[i].node[j].dsw;
  }
}

