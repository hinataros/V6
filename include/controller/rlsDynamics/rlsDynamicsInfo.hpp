/**
   @author Sho Miyahara 2018
*/

namespace RLS{
  struct ControllerInfo{
    int controlModelID;
    Info all;
    TreeModelInfo model;
    ConstraintInfo *constraint;
  };
}
