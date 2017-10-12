#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::velocity(Config &config, Info &info, Vector3d voB, Vector3d wB, VectorXd dth)
{
  if(config.flag.debug) DEBUG;

  // smiyahara: solver内ではB部の速度はvoで扱うためvBは計算しない
  // smiyahara: Base部のsiはすべて0のベクトル
  // smiyahara: 先端部のsiはすべて0のベクトル

  // smiyahara: cross()の関数とかは変数増やせば呼ぶ回数減らせる
  limb[0].node[0].v = voB + cross(wB) * limb[0].node[0].r;
  limb[0].node[0].vC = voB + cross(wB) * limb[0].node[0].rC;

  // 4 spatial momentam
  limb[0].node[0].I = limb[0].node[0].R*limb[0].node[0].Iw_C*limb[0].node[0].R.transpose();
  limb[0].node[0].ISvv = limb[0].node[0].m*Matrix3d::Identity();
  limb[0].node[0].ISvw = -limb[0].node[0].m*cross(limb[0].node[0].rC);
  limb[0].node[0].ISww = -limb[0].node[0].m*cross(limb[0].node[0].rC)*cross(limb[0].node[0].rC).transpose()+limb[0].node[0].I;

  limb[0].node[0].p = limb[0].node[0].ISvv*voB + limb[0].node[0].ISvw*wB;
  limb[0].node[0].lC = limb[0].node[0].ISvw.transpose()*voB + limb[0].node[0].ISww*wB;

  all.p = limb[0].node[0].p;
  all.lC = limb[0].node[0].lC;

  int cur=0, temp;// smiyahara: ホントにこれは無い...
  for(int i=1; i<info.value.node; i++){
    limb[i].node[0].sw = limb[0].node[0].R * limb[i].node[0].jS.tail(3);
    limb[i].node[0].sv = cross(limb[i].node[0].r) * limb[i].node[0].sw;

    limb[i].node[0].vo = voB + limb[i].node[0].sv * dth(cur);
    limb[i].node[0].w = wB + limb[i].node[0].sw * dth(cur);

    limb[i].node[0].v = limb[i].node[0].vo + cross(limb[i].node[0].w) * limb[i].node[0].r;
    limb[i].node[0].vC = limb[i].node[0].vo + cross(limb[i].node[0].w) * limb[i].node[0].rC;

    limb[i].node[0].dsv = cross(wB)*limb[i].node[0].sv + cross(voB)*limb[i].node[0].sw;
    limb[i].node[0].dsw = cross(wB)*limb[i].node[0].sw;

    // 4 spatial momentam
    limb[i].node[0].I = limb[i].node[0].R*limb[i].node[0].Iw_C*limb[i].node[0].R.transpose();

    limb[i].node[0].ISvv = limb[i].node[0].m*Matrix3d::Identity();
    limb[i].node[0].ISvw = -limb[i].node[0].m*cross(limb[i].node[0].rC);
    limb[i].node[0].ISww = -limb[i].node[0].m*cross(limb[i].node[0].rC)*cross(limb[i].node[0].rC).transpose()+limb[i].node[0].I;

    limb[i].node[0].p = limb[i].node[0].ISvv*limb[i].node[0].vo + limb[i].node[0].ISvw*limb[i].node[0].w;
    limb[i].node[0].lC = limb[i].node[0].ISvw.transpose()*limb[i].node[0].vo + limb[i].node[0].ISww*limb[i].node[0].w;

    all.p += limb[i].node[0].p;
    all.lC += limb[i].node[0].lC;

    temp=1;
    for(int j=1; j<info.limb[i].dof; j++){
      limb[i].node[j].sw = limb[i].node[j-1].R * limb[i].node[j].jS.tail(3);
      limb[i].node[j].sv = cross(limb[i].node[j].r) * limb[i].node[j].sw;

      limb[i].node[j].vo = limb[i].node[j-1].vo + limb[i].node[j].sv * dth(cur+j);
      limb[i].node[j].w =  limb[i].node[j-1].w + limb[i].node[j].sw * dth(cur+j);

      limb[i].node[j].v = limb[i].node[j].vo + cross(limb[i].node[j].w) * limb[i].node[j].r;
      limb[i].node[j].vC = limb[i].node[j].vo + cross(limb[i].node[j].w) * limb[i].node[j].rC;

      limb[i].node[j].dsv = cross(limb[i].node[j-1].w)*limb[i].node[j].sv + cross(limb[i].node[j-1].vo)*limb[i].node[j].sw;
      limb[i].node[j].dsw = cross(limb[i].node[j-1].w)*limb[i].node[j].sw;

      // 4 spatial momentam
      limb[i].node[j].I = limb[i].node[j].R*limb[i].node[j].Iw_C*limb[i].node[j].R.transpose();

      limb[i].node[j].ISvv = limb[i].node[j].m*Matrix3d::Identity();
      limb[i].node[j].ISvw = -limb[i].node[j].m*cross(limb[i].node[j].rC);
      limb[i].node[j].ISww = -limb[i].node[j].m*cross(limb[i].node[j].rC)*cross(limb[i].node[j].rC).transpose()+limb[i].node[j].I;

      limb[i].node[j].p = limb[i].node[j].ISvv*limb[i].node[j].vo + limb[i].node[j].ISvw*limb[i].node[j].w;
      limb[i].node[j].lC = limb[i].node[j].ISvw.transpose()*limb[i].node[j].vo + limb[i].node[j].ISww*limb[i].node[j].w;

      all.p += limb[i].node[j].p;
      all.lC += limb[i].node[j].lC;

      temp++;
    }

    // end effector
    limb[i].node[temp].vo = limb[i].node[temp-1].vo;
    limb[i].node[temp].w = limb[i].node[temp-1].w;

    // smiyahara: 上のfor文の中と同じ式になってる省略したい
    limb[i].node[temp].v = limb[i].node[temp].vo + cross(limb[i].node[temp].w) * limb[i].node[temp].r;
    limb[i].node[temp].vC = limb[i].node[temp].vo + cross(limb[i].node[temp].w) * limb[i].node[temp].rC;

    // smiyahara: 先端部のリンクがないと仮定して運動量は計算していない

    cur += temp;
  }

  all.vC = all.p / all.m;
}
