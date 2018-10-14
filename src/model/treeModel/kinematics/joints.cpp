/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"

void RLS::TreeModel::joints()
{
  if(debug) DEBUG;

  // smiyahara: 先端部のejはすべて0のベクトル
  for(int i=0; i<info->linkNum; i++){
    if(i==info->rootNode){
      if(link[i].jointType == "fixed")
        link[i].ej << 0, 0, 0;
      if(link[i].jointType == "free")
        link[i].ej << 1, 1, 1;

    }else{
      if(link[i].jointAxis == "x" || link[i].jointAxis == "X")
        link[i].ej << 1, 0, 0;

      if(link[i].jointAxis == "y" || link[i].jointAxis == "Y")
        link[i].ej << 0, 1, 0;

      if(link[i].jointAxis == "z" || link[i].jointAxis == "Z")
        link[i].ej << 0, 0, 1;
    }
  }
}
