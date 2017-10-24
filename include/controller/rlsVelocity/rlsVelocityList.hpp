#ifndef RLSVELOCITYLIST_HPP_
#define RLSVELOCITYLIST_HPP_

namespace RLS{
  class RlsVelocityList{
  public:
    Vector3d rBDes;
    Vector3d vBDes;

    Vector3d xiBDes;
    Vector3d wBDes;

    VectorXd cal_XDes;
    VectorXd cal_VDes;

    Vector3d erC;
    Vector3d erB;
    Vector3d eoB;

    Vector3d vBRef;
    Vector3d wBRef;
    VectorXd dthRef;

    MatrixXd eePosMatrix;
    MatrixXd eeOrientMatrix;
    MatrixXd eeVelMatrix;
    MatrixXd eeAngVelMatrix;
  };
}

#endif // RLSVELOCITYLIST_HPP_
