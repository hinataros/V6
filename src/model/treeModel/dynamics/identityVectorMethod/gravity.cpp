#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

VectorXd RLS::TreeModel::gravity(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  Vector3d gBf = Vector3d::Zero();
  Vector3d gBn = Vector3d::Zero();
  VectorXd gth = VectorXd::Zero(info.dof.joint);

  Vector3d dvB = -ag;
  limb[0].node[0].dvC_rne = dvB;

  limb[0].node[0].fHat_rne = limb[0].node[0].m*limb[0].node[0].dvC_rne;

  // smiyahara: dv, dw, dvC, fHat, nHatの先端部の要素は計算していない
  int temp=0;// smiyahara: ホントにこれは無い...
  for(int i=1; i<info.value.node; i++){
    for(int j=0; j<info.limb[i].dof; j++){
      if(j==0)
	limb[i].node[0].dv_rne = dvB;
      else
	limb[i].node[j].dv_rne = limb[i].node[j-1].dv_rne;

      limb[i].node[j].dvC_rne = limb[i].node[j].dv_rne;
      limb[i].node[j].fHat_rne = limb[i].node[j].m*limb[i].node[j].dvC_rne;
    }

    temp += info.limb[i].dof;
  }

  for(int i=info.value.joint; i>0; i--){
    for(int j=info.limb[i].dof-1; j>-1; j--){
      if(j==info.limb[i].dof-1){
	limb[i].node[j].f_rne = limb[i].node[j].fHat_rne;
	limb[i].node[j].n_rne = cross(limb[i].node[j].R*limb[i].node[j].ri2C)*limb[i].node[j].fHat_rne;

      }else{
	limb[i].node[j].f_rne = limb[i].node[j].fHat_rne + limb[i].node[j+1].f_rne;
	limb[i].node[j].n_rne = cross(limb[i].node[j].R*limb[i].node[j].ri2C)*limb[i].node[j].fHat_rne
	  + limb[i].node[j+1].n_rne + cross(limb[i].node[j].R*limb[i].node[j+1].d)*limb[i].node[j+1].f_rne;
      }

      gth(temp-info.limb[i].dof+j) = limb[i].node[j].sw.transpose()*limb[i].node[j].n_rne;
    }

    temp -= info.limb[i].dof;
  }

  gBf = limb[0].node[0].fHat_rne;
  gBn = cross(limb[0].node[0].R*limb[0].node[0].ri2C)*limb[0].node[0].fHat_rne;
  for(int i=1; i<info.value.node; i++){
    gBf += limb[i].node[0].f_rne;
    gBn += limb[i].node[0].n_rne + cross(limb[0].node[0].R*limb[i].node[0].d)*limb[i].node[0].f_rne;
  }

  VectorXd g = VectorXd::Zero(info.dof.all);
  g <<
    gBf,
    gBn,
    gth;

  return g;
}
