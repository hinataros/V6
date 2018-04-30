/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::initialize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  ag = Vector3d::Zero();

  for(int i=0; i<info.value.node; i++){
    // smiyahara: 初期化の場所考えたほうがいい
    info.limb[i].contact = false;
    info.limb[i].c = info.limb[i].m = 0;

    for(int j=0; j<info.limb[i].value; j++){
      limb[i].node[j].th0 = 0.;
      limb[i].node[j].dth0 = 0.;

      limb[i].node[j].R0 = Matrix3d::Zero();
      limb[i].node[j].r0 = Vector3d::Zero();
      limb[i].node[j].w0 = Vector3d::Zero();
      limb[i].node[j].v0 = Vector3d::Zero();

      limb[i].node[j].d = Vector3d::Zero();
      limb[i].node[j].ri2C = Vector3d::Zero();

      limb[i].node[j].jS = Vector6d::Zero();
      limb[i].node[j].sv = Vector3d::Zero();
      limb[i].node[j].sw = Vector3d::Zero();

      limb[i].node[j].m = 0.;
      limb[i].node[j].Iw_C = Matrix3d::Zero();
      limb[i].node[j].I = Matrix3d::Zero();

      limb[i].node[j].r = Vector3d::Zero();
      limb[i].node[j].rC = Vector3d::Zero();
      limb[i].node[j].R = Matrix3d::Zero();

      limb[i].node[j].v = Vector3d::Zero();
      limb[i].node[j].vC = Vector3d::Zero();
      limb[i].node[j].w = Vector3d::Zero();
      limb[i].node[j].vo = Vector3d::Zero();

      limb[i].node[j].dsv = Vector3d::Zero();
      limb[i].node[j].dsw = Vector3d::Zero();

      limb[i].node[j].ISvv = Matrix3d::Zero();
      limb[i].node[j].ISvw = Matrix3d::Zero();
      limb[i].node[j].ISww = Matrix3d::Zero();

      limb[i].node[j].p = Vector3d::Zero();
      limb[i].node[j].lC = Vector3d::Zero();

      limb[i].node[j].f = Vector3d::Zero();
      limb[i].node[j].n = Vector3d::Zero();

      limb[i].node[j].dv_rne = Vector3d::Zero();
      limb[i].node[j].dw_rne = Vector3d::Zero();
      limb[i].node[j].dvC_rne = Vector3d::Zero();
      limb[i].node[j].fHat_rne = Vector3d::Zero();
      limb[i].node[j].nHat_rne = Vector3d::Zero();
      limb[i].node[j].f_rne = Vector3d::Zero();
      limb[i].node[j].n_rne = Vector3d::Zero();

    }

    if(i!=0){
      limb[i].J = MatrixXd::Zero(6, info.limb[i].dof); //smiyahara: limb[0]のJが意味ない
      limb[i].dJ = MatrixXd::Zero(6, info.limb[i].dof);
    }
  }

  all.th = all.dth = VectorXd::Zero(info.dof.joint);

  all.m = 0.;
  all.rC = Vector3d::Zero();
  all.vC = Vector3d::Zero();

  all.p = Vector3d::Zero();
  all.lC = Vector3d::Zero();

  all.M = MatrixXd::Zero(info.dof.all, info.dof.all);
  all.c = VectorXd::Zero(info.dof.all);
  all.g = VectorXd::Zero(info.dof.all);
  all.b = VectorXd::Zero(info.dof.all);

  all.dM = MatrixXd::Zero(info.dof.all, info.dof.all);

  all.JB2C = MatrixXd::Zero(3, info.dof.joint);
  all.dJB2C = MatrixXd::Zero(3, info.dof.joint);
  all.MM = MatrixXd::Zero(info.dof.all, info.dof.all);
  all.dMM = MatrixXd::Zero(info.dof.all, info.dof.all);

  // output list
  tm_list.posGifMatrix = MatrixXd::Zero(3, info.value.all);
}
