/**
   @author Sho Miyahara 2017
*/

#ifndef RLSDYNAMICSLIST_HPP_
#define RLSDYNAMICSLIST_HPP_

namespace RLS{
  class RlsDynamicsList{
  public:
    Vector3d rBDes;
    Vector3d vBDes;
    Vector3d dvBDes;
    Vector3d xiBDes;
    Vector3d wBDes;
    Vector3d dwBDes;

    VectorXd cal_XDes;
    VectorXd cal_VDes;
    VectorXd cal_dVDes;

    Vector3d erB;
    Vector3d evB;
    Vector3d eoB;
    Vector3d ewB;

    Vector3d erC;
    Vector3d evC;

    // velocity control
    Vector3d vBRef;
    Vector3d wBRef;
    VectorXd dthRef;

    Vector3d dvBRef;
    Vector3d dwBRef;
    VectorXd ddthRef;

    Vector3d dpRef;
    Vector3d dlRef;

    VectorXd cal_FBarRef;

    VectorXd tau;

    Vector3d pCRB;
    Vector3d lCRB;
    Vector3d pCth;
    Vector3d lTh;
    Vector3d p;
    Vector3d lC;
  };
}

#endif // RLSDYNAMICSLIST_HPP_
