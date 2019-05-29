/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"

void RLS::TreeModel::transformMatrix()
{
  if(debug) DEBUG;

  MatrixXd linkJ = MatrixXd::Zero(6*info->controlNodeNum, info->linkNum);
  MatrixXd linkdJ = MatrixXd::Zero(6*info->controlNodeNum, info->linkNum);

  for(int i=0; i<info->controlNodeNum; i++){
    int node = info->controlNode[i].num;

    all.Rk.block(6*i,6*i,3,3) = all.Rk.block(6*i+3,6*i+3,3,3) = link[node].R;
    all.dRk.block(6*i,6*i,3,3) = all.dRk.block(6*i+3,6*i+3,3,3) = cross(link[node].w)*link[node].R;

    all.TB2k.block(6*i,0,6,6) = Matrix6d::Identity();
    all.TB2k.block(6*i,3,3,3) = -cross(link[node].r - link[info->rootNode].r);
    all.dTB2k.block(6*i,3,3,3) = -cross(link[node].v - link[info->rootNode].v);

    all.TC2k.block(6*i,0,6,6) = Matrix6d::Identity();
    all.TC2k.block(6*i,3,3,3) = -cross(link[node].r - all.rC);
    all.dTC2k.block(6*i,3,3,3) = -cross(link[node].v - all.vC);

    for(int j=node; j!=info->rootNode; j=link[j].parentNode){
      linkJ.block(6*i,0,6,info->linkNum).col(j) <<
        cross(link[j].sw)*(link[node].r - link[j].r),
        link[j].sw;

      linkdJ.block(6*i,0,6,info->linkNum).col(j) <<
        cross(link[j].dsw)*(link[node].r - link[j].r) + cross(link[j].sw)*(link[node].v - link[j].v),
        link[j].dsw;
    }
  }

  all.J = stateMatrixFilter(false,true, linkJ);
  all.dJ = stateMatrixFilter(false,true, linkdJ);
}



void RLS::TreeModel::transformMatrix(VectorXd &offset)
{
  if(debug) DEBUG;

  MatrixXd linkJ = MatrixXd::Zero(6*info->controlNodeNum, info->linkNum);
  MatrixXd linkdJ = MatrixXd::Zero(6*info->controlNodeNum, info->linkNum);

  for(int i=0; i<info->controlNodeNum; i++){
    int node = info->controlNode[i].num;

    // o(i);
    // o(offset.segment(3*i, 3));

    Vector3d linkNode_r = link[node].r + link[node].R*offset.segment(3*i, 3);
    Vector3d linkNode_v = link[node].v + w2dR(link[node].w, link[node].R)*offset.segment(3*i, 3); //offsetぶんの上乗せ
    // if(i==0){
    //   o(offset);
    //   o(linkNode_r);
    //   o(linkNode_v);
    // }

    all.Rk.block(6*i,6*i,3,3) = all.Rk.block(6*i+3,6*i+3,3,3) = link[node].R;
    all.dRk.block(6*i,6*i,3,3) = all.dRk.block(6*i+3,6*i+3,3,3) = w2dR(link[node].w, link[node].R);

    all.TB2k.block(6*i,0,6,6) = Matrix6d::Identity();
    all.TB2k.block(6*i,3,3,3) = -cross(linkNode_r - link[info->rootNode].r);
    all.dTB2k.block(6*i,3,3,3) = -cross(linkNode_v - link[info->rootNode].v);

    all.TC2k.block(6*i,0,6,6) = Matrix6d::Identity();
    all.TC2k.block(6*i,3,3,3) = -cross(linkNode_r - all.rC);
    all.dTC2k.block(6*i,3,3,3) = -cross(linkNode_v - all.vC);

    for(int j=node; j!=info->rootNode; j=link[j].parentNode){
      linkJ.block(6*i,0,6,info->linkNum).col(j) <<
        cross(link[j].sw)*(linkNode_r - link[j].r),
        link[j].sw;

      linkdJ.block(6*i,0,6,info->linkNum).col(j) <<
        cross(link[j].dsw)*(linkNode_r - link[j].r) + cross(link[j].sw)*(linkNode_v - link[j].v),
        link[j].dsw;
    }
  }

  all.J = stateMatrixFilter(false,true, linkJ);
  all.dJ = stateMatrixFilter(false,true, linkdJ);
}
