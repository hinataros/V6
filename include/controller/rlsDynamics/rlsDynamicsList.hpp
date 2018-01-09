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

    Vector3d rXDes;
    Vector3d drXDes;

    VectorXd cal_XDes;
    VectorXd cal_VDes;
    VectorXd cal_dVDes;

    Vector3d erB;
    Vector3d evB;
    Vector3d eoB;
    Vector3d ewB;

    Vector3d eX;

    Vector3d erC;
    Vector3d evC;

    VectorXd cal_Ep;
    VectorXd cal_Ev;

    VectorXd cal_FErr;

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

    Vector6d cal_FextRef;

    VectorXd tau;

    Vector3d pCRB;
    Vector3d lCRB;
    Vector3d pCth;
    Vector3d lCth;
    Vector3d p;
    Vector3d lC;

    Vector2d rp;
    VectorXd rpk;
    Vector3d rX;
  };
}

#endif // RLSDYNAMICSLIST_HPP_
