#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::jacobian(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  Vector3d eePos = Vector3d::Zero();

  for(int i=1; i<info.value.node; i++){
    eePos = limb[i].node[info.limb[i].dof].r;

    for(int j=0; j<info.limb[i].dof; j++){
      limb[i].J.col(j) <<
	cross(limb[i].node[j].sw) * (eePos - limb[i].node[j].r),
	limb[i].node[j].sw;
    }
  }
}
