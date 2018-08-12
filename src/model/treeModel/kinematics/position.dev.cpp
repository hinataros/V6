/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::position(Config &config, Info &info, Vector3d rB, Matrix3d RB, VectorXd th)
{
  if(config.flag.debug) DEBUG;

  limb[0].node[0].rC = rB + RB*limb[0].node[0].ri2C;
  all.rC = (limb[0].node[0].rC*limb[0].node[0].m)/all.m;

  int cur=0, temp;// smiyahara: 無いなこれは...
  for(int i=1; i<info.value.node; i++){
    limb[i].node[0].R = RB*R(limb[i].node[0].jointType, th(cur));
    limb[i].node[0].r = rB + RB*limb[i].node[0].d;

    limb[i].node[0].rC = limb[i].node[0].r + limb[i].node[0].R*limb[i].node[0].ri2C;
    all.rC += (limb[i].node[0].rC*limb[i].node[0].m)/all.m;

    temp=1;
    for(int j=1; j<info.limb[i].dof; j++){
      limb[i].node[j].R = limb[i].node[j-1].R*R(limb[i].node[j].jointType, th(cur+j));
      limb[i].node[j].r = limb[i].node[j-1].r + limb[i].node[j-1].R*limb[i].node[j].d;

      limb[i].node[j].rC = limb[i].node[j].r + limb[i].node[j].R*limb[i].node[j].ri2C;
      all.rC += (limb[i].node[j].rC*limb[i].node[j].m)/all.m;

      temp++;
    }

    limb[i].node[temp].R = limb[i].node[temp-1].R;
    limb[i].node[temp].r = limb[i].node[temp-1].r + limb[i].node[temp-1].R*limb[i].node[temp].d;

    limb[i].node[temp].rC = limb[i].node[temp].r + limb[i].node[temp].R*limb[i].node[temp].ri2C;
    all.rC += (limb[i].node[temp].rC*limb[i].node[temp].m)/all.m;

    cur += temp;
  }
}
