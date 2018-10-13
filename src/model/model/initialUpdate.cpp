/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::initialUpdate()
{
  if(debug) DEBUG;

  for(int i=0; i<info.treeModelNum; i++){
    int rootNode = info.treeModel[i].rootNode;

    treeModel[i].link[rootNode].r = treeModel[i].link[rootNode].r0;
    treeModel[i].link[rootNode].R = treeModel[i].link[rootNode].R0;
    treeModel[i].link[rootNode].vo = treeModel[i].link[rootNode].vo0;
    treeModel[i].link[rootNode].w = treeModel[i].link[rootNode].w0;
    treeModel[i].writeJointStateVector("joint angle", treeModel[i].readJointStateVector("initial joint angle"));
    treeModel[i].writeJointStateVector("joint velocity", treeModel[i].readJointStateVector("initial joint velocity"));
  }

  update();
}