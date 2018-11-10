/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::outputConfig()
{
  if(debug) DEBUG;

  outputList.rB = link[info->rootNode].r;
  outputList.RB = link[info->rootNode].R;
  outputList.xiB = antiDiag(3,1.,1.,1.)*R2xi(link[info->rootNode].R);
  outputList.vB = link[info->rootNode].v;
  outputList.wB = link[info->rootNode].w;
  outputList.th = readJointState("joint angle");
  outputList.dth = readJointState("joint velocity");

  outputList.rC = all.rC;
  outputList.vC = all.vC;

  outputList.p = all.p;
  outputList.lC = all.lC;

  outputList.r = readControlNodeValue("position");
  outputList.v = readControlNodeValue("velocity");

  MatrixXd antiDiagMat = MatrixXd::Zero(3*info->controlNodeNum,3*info->controlNodeNum);
  for(int i=0; i<info->controlNodeNum; i++)
    antiDiagMat.block(3*i,3*i,3,3) = antiDiag(3,1.,1.,1.);
  outputList.xi = antiDiagMat*readControlNodeValue("orientation");
  outputList.w = readControlNodeValue("angular velocity");
  outputList.f = readControlNodeValue("force");
  outputList.n = readControlNodeValue("moment");

  // // smiyahara: サイズの初期化の変数がびみょ
  // int cur=0, temp=0;
  // for(int i=0; i<info->value.node; i++){
  //   temp=0;
  //   for(int j=0; j<info->limb[i].value; j++){
  //     outputList.posGifMatrix.col(cur+j) = limb[i].node[j].r;
  //     temp++;
  //   }

  //   cur+=temp;
  // }
}
