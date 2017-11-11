#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::outputConfig(Config &config, Info &info)
{
  if (config.flag.debug) DEBUG;

  tm_list.rB = limb[0].node[0].r;
  tm_list.RB = limb[0].node[0].R;
  tm_list.xiB = R2xi(limb[0].node[0].R);
  tm_list.vB = limb[0].node[0].v;
  tm_list.wB = limb[0].node[0].w;
  tm_list.th = all.th;
  tm_list.dth = all.dth;

  tm_list.rC = all.rC;
  tm_list.vC = all.vC;

  tm_list.p = all.p;
  tm_list.lC = all.lC;

  for(int i=1; i<info.value.node; i++){
    tm_list.eePosMatrix.col(i-1) = limb[i].node[info.limb[i].dof].r;
    tm_list.eeOrientMatrix.col(i-1) = R2xi(limb[i].node[info.limb[i].dof].R);
    tm_list.eeVelMatrix.col(i-1) = limb[i].node[info.limb[i].dof].v;
    tm_list.eeAngVelMatrix.col(i-1) = limb[i].node[info.limb[i].dof].w;
  }

  // smiyahara: サイズの初期化の変数がびみょ
  int cur=0, temp=0;
  for(int i=0; i<info.value.node; i++){
    temp=0;
    for(int j=0; j<info.limb[i].value; j++){
      tm_list.posGifMatrix.col(cur+j) = limb[i].node[j].r;
      temp++;
    }

    cur+=temp;
  }
}
