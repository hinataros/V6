/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::setState2Model(Model &model)
{
  if(debug) DEBUG;

  for(int i=0; i<model.info.treeModelNum; i++){
    int rootNode = model.info.treeModel[i].rootNode;

    model.treeModel[i].link[rootNode].r = state[i].rB;
    model.treeModel[i].link[rootNode].R = state[i].RB;
    model.treeModel[i].link[rootNode].vo = state[i].voB;
    model.treeModel[i].link[rootNode].w = state[i].wB;

    model.treeModel[i].writeJointState("joint angle", state[i].th);
    model.treeModel[i].writeJointState("joint velocity", state[i].dth);
  }
}
