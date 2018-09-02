/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::setInfo()
{
  if(debug) DEBUG;

  if(link[info.rootNode].jointType=="fixed")
    info.dof.root = 0;
  else if(link[info.rootNode].jointType=="free")
    info.dof.root = 6;

  info.dof.all = info.dof.root + info.dof.joint;

  // smiyahara: link[0].parentNode is 0 (no initialized)
  for(int i=0; i<info.linkNum; i++)
    for(int j=0; j<info.linkNum; j++)
      if(link[i].parent==link[j].name)
        link[i].parentNode = j;

  for(int i=0; i<info.controlNodeNum; i++){
    bool flag = false;
    for(int j=0; j<info.linkNum; j++){
      if(link[j].name==info.controlNode[i].name){
        info.controlNode[i].num = j;
        flag = true;
      }
    }

    if(!flag){
      cout << "not found '" << info.controlNode[i].name << "' node"<< endl;
      info.controlNode[i].num = 0;
    }
  }
}
