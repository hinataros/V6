/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"

void RLS::TreeModel::joints(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  // smiyahara: Base部のjSは本当は6*6のMatrixにしたいがまだしていない
  // smiyahara: 先端部のjSはすべて0のベクトル
  for(int i=1; i<info.value.node; i++)
    for(int j=0; j<info.limb[i].dof; j++){
      if(limb[i].node[j].jointType == "x")
	limb[i].node[j].jS << 0, 0, 0, 1, 0, 0;

      if(limb[i].node[j].jointType == "y")
	limb[i].node[j].jS << 0, 0, 0, 0, 1, 0;

      if(limb[i].node[j].jointType == "z")
	limb[i].node[j].jS << 0, 0, 0, 0, 0, 1;
    }
}
