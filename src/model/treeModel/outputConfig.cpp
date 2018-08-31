/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::outputConfig()
{
  if(debug) DEBUG;

  tm_list.rB = link[info.rootNode].r;
  tm_list.RB = link[info.rootNode].R;
  tm_list.xiB = antiDiag(3,1.,1.,1.)*R2xi(link[info.rootNode].R);
  tm_list.vB = link[info.rootNode].v;
  tm_list.wB = link[info.rootNode].w;
  tm_list.th = readJointStateVector("joint angle");
  tm_list.dth = readJointStateVector("joint velocity");

  tm_list.rC = all.rC;
  tm_list.vC = all.vC;

  tm_list.p = all.p;
  tm_list.lC = all.lC;

  tm_list.r = readEndEffectorValueVector("position");
  tm_list.v = readEndEffectorValueVector("velocity");

  MatrixXd antiDiagMat = MatrixXd::Zero(3*info.eeNum,3*info.eeNum);
  for(int i=0; i<info.eeNum; i++)
    antiDiagMat.block(3*i,3*i,3,3) = antiDiag(3,1.,1.,1.);
  tm_list.xi = antiDiagMat*readEndEffectorValueVector("orientation");
  tm_list.w = readEndEffectorValueVector("angular velocity");
  tm_list.f = readEndEffectorValueVector("force");
  tm_list.n = readEndEffectorValueVector("moment");

  // // smiyahara: サイズの初期化の変数がびみょ
  // int cur=0, temp=0;
  // for(int i=0; i<info.value.node; i++){
  //   temp=0;
  //   for(int j=0; j<info.limb[i].value; j++){
  //     tm_list.posGifMatrix.col(cur+j) = limb[i].node[j].r;
  //     temp++;
  //   }

  //   cur+=temp;
  // }
}
