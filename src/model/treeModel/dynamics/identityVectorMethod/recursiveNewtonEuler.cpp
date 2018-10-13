/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

VectorXd RLS::TreeModel::recursiveNewtonEuler()
{
  if(debug) DEBUG;

  link[0].dv_rne -= worldModel->ag;

  for(int i=0; i<info->linkNum; i++){
    if(i!=info->rootNode){
      link[i].dv_rne =
        link[link[i].parentNode].dv_rne + cross(link[link[i].parentNode].dw_rne)*link[link[i].parentNode].R*link[i].d
        + cross(link[link[i].parentNode].w)*(cross(link[link[i].parentNode].w)*link[link[i].parentNode].R*link[i].d);

      link[i].dw_rne = link[link[i].parentNode].dw_rne + link[i].sw*link[i].ddth_rne + cross(link[link[i].parentNode].w)*link[i].sw*link[i].dth;
    }

    link[i].dvC_rne = link[i].dv_rne + cross(link[i].dw_rne)*link[i].R*link[i].ri2C + cross(link[i].w)*(cross(link[i].w)*link[i].R*link[i].ri2C);

    link[i].fHat_rne = link[i].m*link[i].dvC_rne;
    link[i].nHat_rne = link[i].I*link[i].dw_rne + cross(link[i].w)*link[i].I*link[i].w;
  }

  // initialize
  for(int i=0; i<info->linkNum; i++){
    link[i].f_rne = link[i].fHat_rne;
    // // smiyahara: 先端部にかかる外力(先端部のみ)
    // + link[i+1].f;
    link[i].n_rne = link[i].nHat_rne + cross(link[i].R*link[i].ri2C)*link[i].fHat_rne;
    // // smiyahara: 先端部にかかる外力(先端部のみ)
    // + link[i+1].n + cross(link[i].R*link[i+1].d)*link[i+1].f;
  }

  // smiyahara: デクリメントしながら足していくから、枝分かれする前から順に小さい数字じゃないとダメ（説明がむずい）
  for(int i=info->linkNum-1; i>-1; i--){
    if(i!=info->rootNode){
      link[link[i].parentNode].f_rne += link[i].f_rne;
      link[link[i].parentNode].n_rne += link[i].n_rne + cross(link[link[i].parentNode].R*link[i].d)*link[i].f_rne;
    }
  }

  for(int i=0; i<info->linkNum; i++)
    link[i].tau_rne = link[i].sw.transpose()*link[i].n_rne;

  return (VectorXd(info->dof.all)<<link[info->rootNode].f_rne,link[info->rootNode].n_rne,readJointStateVector("rne torque")).finished();
}
