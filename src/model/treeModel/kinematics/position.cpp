/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::position()
{
  if(debug) DEBUG;

  // initialize
  all.rC = Vector3d::Zero();

  for(int i=0; i<info.linkNum; i++){
    if(i!=info.rootNode){
      link[i].R = link[link[i].parentNode].R*R(link[i].jointAxis, link[i].th);
      link[i].r = link[link[i].parentNode].r + link[link[i].parentNode].R*link[i].d;
    }

    // smiyahara:
    // if link[i].ri2C = 0 => link[i].rC = link[i].r
    // if link[i].m = 0 => rC = r
    link[i].rC = link[i].r + link[i].R*link[i].ri2C;
    all.rC += (link[i].rC*link[i].m)/all.m;
  }
}
