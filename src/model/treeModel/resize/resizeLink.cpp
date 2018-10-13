/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::resizeLink()
{
  if(debug) DEBUG;

  for(int i=0; i<info->linkNum; i++){
    link[i].active = false;

    link[i].th0 = 0.;
    link[i].dth0 = 0.;

    link[i].R0 = Matrix3d::Zero();
    link[i].r0 = Vector3d::Zero();
    link[i].w0 = Vector3d::Zero();
    link[i].v0 = Vector3d::Zero();

    link[i].th = 0.;
    link[i].dth = 0.;

    link[i].d = Vector3d::Zero();
    link[i].ri2C = Vector3d::Zero();

    link[i].ej = Vector3d::Zero();
    link[i].sv = Vector3d::Zero();
    link[i].sw = Vector3d::Zero();

    link[i].m = 0.;
    link[i].Iw_C = Matrix3d::Zero();
    link[i].I = Matrix3d::Zero();

    link[i].r = Vector3d::Zero();
    link[i].rC = Vector3d::Zero();
    link[i].R = Matrix3d::Zero();

    link[i].v = Vector3d::Zero();
    link[i].vC = Vector3d::Zero();
    link[i].w = Vector3d::Zero();
    link[i].vo = Vector3d::Zero();

    link[i].dsv = Vector3d::Zero();
    link[i].dsw = Vector3d::Zero();

    link[i].ISvv = Matrix3d::Zero();
    link[i].ISvw = Matrix3d::Zero();
    link[i].ISww = Matrix3d::Zero();

    link[i].p = Vector3d::Zero();
    link[i].lC = Vector3d::Zero();

    link[i].f = Vector3d::Zero();
    link[i].n = Vector3d::Zero();

    link[i].Jvi = MatrixXd::Zero(3,info->linkNum);
    link[i].Jwi = MatrixXd::Zero(3,info->linkNum);
    link[i].dJvi = MatrixXd::Zero(3,info->linkNum);
    link[i].dJwi = MatrixXd::Zero(3,info->linkNum);

    link[i].dv_rne = Vector3d::Zero();
    link[i].dw_rne = Vector3d::Zero();
    link[i].dvC_rne = Vector3d::Zero();
    link[i].ddth_rne = 0.;
    link[i].fHat_rne = Vector3d::Zero();
    link[i].nHat_rne = Vector3d::Zero();
    link[i].f_rne = Vector3d::Zero();
    link[i].n_rne = Vector3d::Zero();
    link[i].tau_rne = 0.;
  }

  all.m = 0.;
}
