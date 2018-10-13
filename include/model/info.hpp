/**
   @author Sho Miyahara 2018
*/

#ifndef INFO_HPP_
#define INFO_HPP_

#include <map>

namespace RLS{
  struct Dof{
    int all;
    int root;
    int joint;
  };

  // smiyahara: 別の名前希望
  struct ID{
    string name;
    int num;
  };

  struct TreeModelInfo{
    string name;
    int rootNode;
    int linkNum;

    map<string, int> controlNodeID;
    int controlNodeNum;
    int sensorNodeNum;
    ID *controlNode;
    ID *sensorNode;

    Dof dof;
  };

  struct RigidBodyModelInfo{
    string name;
  };

  struct Info{
    map<string,int> modelID;
    int treeModelNum;
    int rigidBodyModelNum;

    TreeModelInfo *treeModel;
    RigidBodyModelInfo *rigidBodyModel;
  };
}

#endif // INFO_HPP_
