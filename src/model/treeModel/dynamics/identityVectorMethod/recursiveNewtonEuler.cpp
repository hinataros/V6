#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

VectorXd RLS::TreeModel::recursiveNewtonEuler(Config &config, Info &info, Vector3d dvB, Vector3d dwB, VectorXd ddth)
{
  if(config.flag.debug) DEBUG;

  Vector3d fB = Vector3d::Zero();
  Vector3d nB = Vector3d::Zero();
  VectorXd tau = VectorXd::Zero(info.dof.joint);

  dvB -= ag;

  limb[0].node[0].dvC_rne = dvB + cross(dwB)*limb[0].node[0].R*limb[0].node[0].ri2C
    + cross(limb[0].node[0].w)*(cross(limb[0].node[0].w)*limb[0].node[0].R*limb[0].node[0].ri2C);

  limb[0].node[0].fHat_rne = limb[0].node[0].m*limb[0].node[0].dvC_rne;
  limb[0].node[0].nHat_rne = limb[0].node[0].I*dwB + cross(limb[0].node[0].w)*limb[0].node[0].I*limb[0].node[0].w;
  // smiyahara: dv, dw, dvC, fHat, nHatの先端部の要素は計算していない
  int temp=0;// smiyahara: ホントにこれは無い...
  for(int i=1; i<info.value.node; i++){
    for(int j=0; j<info.limb[i].dof; j++){
      if(j==0){
        limb[i].node[0].dv_rne = dvB + cross(dwB)*limb[0].node[0].R*limb[i].node[0].d
          + cross(limb[0].node[0].w)*(cross(limb[0].node[0].w)*limb[0].node[0].R*limb[i].node[0].d);

        limb[i].node[0].dw_rne = dwB + limb[i].node[0].sw*ddth(temp+j)
          + cross(limb[0].node[0].w)*limb[i].node[0].sw*all.dth(temp+j);

      }else{
        limb[i].node[j].dv_rne = limb[i].node[j-1].dv_rne + cross(limb[i].node[j-1].dw_rne)*limb[i].node[j-1].R*limb[i].node[j].d
          + cross(limb[i].node[j-1].w)*(cross(limb[i].node[j-1].w)*limb[i].node[j-1].R*limb[i].node[j].d);

        limb[i].node[j].dw_rne = limb[i].node[j-1].dw_rne + limb[i].node[j].sw*ddth(temp+j)
          + cross(limb[i].node[j-1].w)*limb[i].node[j].sw*all.dth(temp+j);
      }

      limb[i].node[j].dvC_rne = limb[i].node[j].dv_rne + cross(limb[i].node[j].dw_rne)*limb[i].node[j].R*limb[i].node[j].ri2C
        + cross(limb[i].node[j].w)*(cross(limb[i].node[j].w)*limb[i].node[j].R*limb[i].node[j].ri2C);

      limb[i].node[j].fHat_rne = limb[i].node[j].m*limb[i].node[j].dvC_rne;
      limb[i].node[j].nHat_rne = limb[i].node[j].I*limb[i].node[j].dw_rne
        + cross(limb[i].node[j].w)*limb[i].node[j].I*limb[i].node[j].w;

    }

    temp += info.limb[i].dof;
  }

  for(int i=info.value.joint; i>0; i--){
    for(int j=info.limb[i].dof-1; j>-1; j--){
      if(j==info.limb[i].dof-1){
        limb[i].node[j].f_rne = limb[i].node[j].fHat_rne;
        // // // smiyahara: 先端部にかかる外力
        // + limb[i].node[j+1].f;
        limb[i].node[j].n_rne = limb[i].node[j].nHat_rne + cross(limb[i].node[j].R*limb[i].node[j].ri2C)*limb[i].node[j].fHat_rne;
        // // smiyahara: 先端部にかかる外力
        // + limb[i].node[j+1].n + cross(limb[i].node[j].R*limb[i].node[j+1].d)*limb[i].node[j+1].f;

      }else{
        limb[i].node[j].f_rne = limb[i].node[j].fHat_rne + limb[i].node[j+1].f_rne;
        limb[i].node[j].n_rne = limb[i].node[j].nHat_rne + cross(limb[i].node[j].R*limb[i].node[j].ri2C)*limb[i].node[j].fHat_rne
          + limb[i].node[j+1].n_rne + cross(limb[i].node[j].R*limb[i].node[j+1].d)*limb[i].node[j+1].f_rne;
      }

      tau(temp-info.limb[i].dof+j) = limb[i].node[j].sw.transpose()*limb[i].node[j].n_rne;
    }

    temp -= info.limb[i].dof;
  }

  fB = limb[0].node[0].fHat_rne;
  nB = limb[0].node[0].nHat_rne + cross(limb[0].node[0].R*limb[0].node[0].ri2C)*limb[0].node[0].fHat_rne;

  for(int i=1; i<info.value.node; i++){
    fB += limb[i].node[0].f_rne;
    nB += limb[i].node[0].n_rne + cross(limb[0].node[0].R*limb[i].node[0].d)*limb[i].node[0].f_rne;
  }

  VectorXd cal_Q = VectorXd::Zero(info.dof.all);
  cal_Q <<
    fB,
    nB,
    tau;

  return cal_Q;
}
