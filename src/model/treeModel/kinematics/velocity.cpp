/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::velocity()
{
  if(debug) DEBUG;

  // initialize
  all.p = all.lC = Vector3d::Zero();

  for(int i=0; i<info->linkNum; i++){
    // link[rootNode].sw = 0
    if(i!=info->rootNode){
      link[i].sw = link[link[i].parentNode].R*link[i].ej;
      link[i].sv = cross(link[i].r)*link[i].sw;

      // smiyahara: cross()の関数とかは変数増やせば呼ぶ回数減らせる
      link[i].vo = link[link[i].parentNode].vo + link[i].sv*link[i].dth;
      link[i].w = link[link[i].parentNode].w + link[i].sw*link[i].dth;

      link[i].dsv =
        cross(link[link[i].parentNode].w)*link[i].sv
        + cross(link[link[i].parentNode].vo)*link[1].sw;
      link[i].dsw = cross(link[link[i].parentNode].w)*link[i].sw;
    }

    link[i].v = link[i].vo + cross(link[i].w)*link[i].r;
    link[i].vC = link[i].vo + cross(link[i].w)*link[i].rC;

    link[i].I = link[i].R*link[i].Iw_C*link[i].R.transpose();

    link[i].ISvv = link[i].m*Matrix3d::Identity();
    link[i].ISvw = -link[i].m*cross(link[i].rC);
    link[i].ISww = link[i].m*cross(link[i].rC)*cross(link[i].rC).transpose() + link[i].I;

    link[i].p = link[i].ISvv*link[i].vo + link[i].ISvw*link[i].w;
    link[i].lC = link[i].ISvw.transpose()*link[i].vo + link[i].ISww*link[i].w;

    all.p += link[i].p;
    all.lC += link[i].lC;
  }

  all.vC = all.p / all.m;
}
