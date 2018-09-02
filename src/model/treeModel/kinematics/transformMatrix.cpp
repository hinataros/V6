/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"

void RLS::TreeModel::transformMatrix()
{
  if(debug) DEBUG;

  MatrixXd linkJ = MatrixXd::Zero(6*info.controlNodeNum, info.linkNum);
  MatrixXd linkdJ = MatrixXd::Zero(6*info.controlNodeNum, info.linkNum);

  for(int i=0; i<info.controlNodeNum; i++){
    int node = info.controlNode[i].num;

    all.Rk.block(6*i,6*i,3,3) = all.Rk.block(6*i+3,6*i+3,3,3) = link[node].R;
    all.dRk.block(6*i,6*i,3,3) = all.dRk.block(6*i+3,6*i+3,3,3) = cross(link[node].w)*link[node].R;

    all.TB2k.block(6*i,0,6,6) = Matrix6d::Identity();
    all.TB2k.block(6*i,3,3,3) = -cross(link[node].r - link[info.rootNode].r);
    all.dTB2k.block(6*i,3,3,3) = -cross(link[node].v - link[info.rootNode].v);

    all.TC2k.block(6*i,0,6,6) = Matrix6d::Identity();
    all.TC2k.block(6*i,3,3,3) = -cross(link[node].r - all.rC);
    all.dTC2k.block(6*i,3,3,3) = -cross(link[node].v - all.vC);

    for(int j=node; j!=info.rootNode; j=link[j].parentNode){
      linkJ.block(6*i,0,6,info.linkNum).col(j) <<
        cross(link[j].sw)*(link[node].r - link[j].r),
        link[j].sw;

      linkdJ.block(6*i,0,6,info.linkNum).col(j) <<
        cross(link[j].dsw)*(link[node].r - link[j].r) + cross(link[j].sw)*(link[node].v - link[j].v),
        link[j].dsw;
    }
  }

  all.J = stateMatrixFilter(false,true, linkJ);
  all.dJ = stateMatrixFilter(false,true, linkdJ);
}
