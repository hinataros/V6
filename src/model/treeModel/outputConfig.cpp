/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::outputConfig(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  tm_list.rB = limb[0].node[0].r;
  tm_list.RB = limb[0].node[0].R;
  tm_list.xiB = antiDiag(3,1.,1.,1.)*R2xi(limb[0].node[0].R);
  tm_list.vB = limb[0].node[0].v;
  tm_list.wB = limb[0].node[0].w;
  tm_list.th = all.th;
  tm_list.dth = all.dth;

  tm_list.rC = all.rC;
  tm_list.vC = all.vC;

  tm_list.p = all.p;
  tm_list.lC = all.lC;

  tm_list.r = tm_list.v =
    tm_list.xi = tm_list.w =
    tm_list.f = tm_list.n = VectorXd::Zero(3*info.value.joint);
  for(int i=1; i<info.value.node; i++){
    tm_list.r.segment(3*(i-1), 3) = limb[i].node[info.limb[i].dof].r;
    tm_list.xi.segment(3*(i-1), 3) = antiDiag(3,1.,1.,1.)*R2xi(limb[i].node[info.limb[i].dof].R);

    tm_list.v.segment(3*(i-1), 3) = limb[i].node[info.limb[i].dof].v;
    tm_list.w.segment(3*(i-1), 3) = limb[i].node[info.limb[i].dof].w;

    tm_list.f.segment(3*(i-1), 3) = limb[i].node[info.limb[i].dof].f;
    tm_list.n.segment(3*(i-1), 3) = limb[i].node[info.limb[i].dof].n;
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
