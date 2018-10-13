/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::initialParameter(Model &model)
{
  if(debug) DEBUG;

  t = model.worldModel.t0;

  for(int i=0; i<model.info.treeModelNum; i++){
    int rootNode = model.info.treeModel[i].rootNode;

    // B部の初期位置
    state[i].rB = model.treeModel[i].link[rootNode].r0;

    // B部の初期姿勢
    state[i].RB = model.treeModel[i].link[rootNode].R0;

    // B部の初期空間速度
    state[i].voB = model.treeModel[i].link[rootNode].vo0;

    // B部の初期角速度
    state[i].wB = model.treeModel[i].link[rootNode].w0;

    // 関節の初期状態
    state[i].th = model.treeModel[i].readJointStateVector("initial joint angle");
    state[i].dth = model.treeModel[i].readJointStateVector("initial joint velocity");
  }
}
