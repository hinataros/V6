/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"

void RLS::TreeModel::transformMatrix()
{
  if(debug) DEBUG;

  MatrixXd linkJ = MatrixXd::Zero(6*info.eeNum, info.linkNum);
  MatrixXd linkdJ = MatrixXd::Zero(6*info.eeNum, info.linkNum);

  int eeNode[info.eeNum];
  Vector3d eePos[info.eeNum];
  Vector3d eeVel[info.eeNum];

  for(int i=0, j=0; i<info.linkNum; i++){
    if(link[i].linkType=="end effector"){
      eeNode[j] = i;
      eePos[j] = link[i].r;
      eeVel[j] = link[i].v;
      // eePos[j] = link[i].r + model.limb[k].node[info.limb[k].dof].R*offset
      // eeVel[j] = link[i].v + w2dR(model.limb[k].node[info.limb[k].dof].w, model.limb[k].node[info.limb[k].dof].R)*offset;
      j++;
    }
  }

  for(int i=info.eeNum-1; i>-1; i--){
    all.Rk.block(6*i,6*i,3,3) =
      all.Rk.block(6*i+3,6*i+3,3,3) = link[i].R;
    all.dRk.block(6*i,6*i,3,3) =
      all.dRk.block(6*i+3,6*i+3,3,3) = cross(link[i].w)*link[i].R;

    all.TB2k.block(6*i,0,6,6) = Matrix6d::Identity();
    all.TB2k.block(6*i,3,3,3)= -cross(eePos[i] - link[info.rootNode].r);
    all.dTB2k.block(6*i,3,3,3)= -cross(eeVel[i] - link[info.rootNode].v);

    all.TC2k.block(6*i,0,6,6) = Matrix6d::Identity();
    all.TC2k.block(6*i,3,3,3)= -cross(eePos[i] - all.rC);
    all.dTC2k.block(6*i,3,3,3)= -cross(eeVel[i] - all.vC);

    for(int j=eeNode[i]; j!=info.rootNode; j=link[j].parentNode){
      linkJ.block(6*i,0,6,info.linkNum).col(j) <<
        cross(link[j].sw)*(eePos[i] - link[j].r),
        link[j].sw;

      linkdJ.block(6*i,0,6,info.linkNum).col(j) <<
        cross(link[j].dsw)*(eePos[i] - link[j].r) + cross(link[j].sw)*(eeVel[i] - link[j].v),
        link[j].dsw;
    }
  }

  all.J = stateMatrixFilter(false,true, linkJ);
  all.dJ = stateMatrixFilter(false,true, linkdJ);

  // o(all.J);
  // o(all.dJ);
  // o(all.TB2k);
  // o(all.dTB2k);
  // o(all.TC2k);
  // o(all.dTC2k);
  // gc;
}
