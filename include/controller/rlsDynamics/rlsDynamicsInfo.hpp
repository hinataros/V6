/**
   @author Sho Miyahara 2018
*/

namespace RLS{
  // smiyahara: 良い名前が浮かばなかった
  struct Node{
    int all;
    int *controlNode;
    int axis[6];
  };

  struct Constraint{
    Node c;
    Node m;
  };

  struct ControllerInfo{
    int controlModelID;
    Info all;
    TreeModelInfo model;
    Constraint constraint;
  };
}
