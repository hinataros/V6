#ifndef RLSACCELERATIONLIST_HPP_
#define RLSACCELERATIONLIST_HPP_

namespace RLS{
  class RlsAccelerationList{
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

    Vector3d dvBRef;
    Vector3d dwBRef;
    VectorXd ddthRef;
  };
}

#endif // RLSACCELERATIONLIST_HPP_
