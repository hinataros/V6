/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

VectorXd RLS::TreeModel::gravity()
{
  if(debug) DEBUG;

  link[0].dv_rne = -worldModel->ag;

  for(int i=0; i<info->linkNum; i++){
    if(i!=info->rootNode)
      link[i].dv_rne = link[link[i].parentNode].dv_rne;

    link[i].dvC_rne = link[i].dv_rne;
    link[i].fHat_rne = link[i].m*link[i].dvC_rne;
  }

  // initialize
  for(int i=0; i<info->linkNum; i++){
    link[i].f_rne = link[i].fHat_rne;
    link[i].n_rne = cross(link[i].R*link[i].ri2C)*link[i].fHat_rne;
  }

  for(int i=info->linkNum-1; i>-1; i--){
    if(i!=info->rootNode){
      link[link[i].parentNode].f_rne += link[i].f_rne;
      link[link[i].parentNode].n_rne += link[i].n_rne + cross(link[link[i].parentNode].R*link[i].d)*link[i].f_rne;
    }
  }

  for(int i=0; i<info->linkNum; i++)
    link[i].tau_rne = link[i].sw.transpose()*link[i].n_rne;

  return (VectorXd(info->dof.all)<<link[info->rootNode].f_rne,link[info->rootNode].n_rne,readJointState("rne torque")).finished();
}
