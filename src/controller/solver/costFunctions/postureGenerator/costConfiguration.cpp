#include "config.hpp"
#include "common.hpp"
#include "model.hpp"
#include "info.hpp"

#include "postureGenerator.hpp"


RLS::postureGenerator::postureGenerator()
{
  nparam = 0;
  ni = 0;
  ne = 0;
}

RLS::postureGenerator::~postureGenerator()
{

}


void RLS::postureGenerator::configuration(TreeModelInfo &info, TreeModel &model)
{
  int i, j;

  // limbs = info.dof.joint;
  // for(i=1; i<limbs; i++) {
  //   dof[i] = info.limb[i].dof;
  //
  //   for(j=0; j<dof[i]) {
  //     mk[i][j] = model.limb[i].node[j].m;
  //     lk[i][j] = model.limb[i].node[j].d;
  //     r2Ck[i][j] = model.limb[i].node[j].ri2C;
  //     jTk[i][j] = model.limb[i].node[j].jointType;
  //   }
  // }
  // mall = model.all.m;
}
