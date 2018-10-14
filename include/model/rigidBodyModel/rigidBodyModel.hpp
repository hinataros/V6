/**
   @author Sho Miyahara 2018
*/

#ifndef RIGIDBODYMODEL_HPP_
#define RIGIDBODYMODEL_HPP_

// #include "rigidBodyModelList.hpp"
#include "info.hpp"

namespace RLS{
  class RigidBodyModel{
  private:
    int uniqueNum;

  public:
    double mO;
    Vector3d xiO0;
    Vector3d rO0;
    Vector3d wO0;
    Vector3d vO0;// 今のところyamlから読むとき、B部のみが必要

    Matrix3d Iw_C;
    Matrix3d I;

    Vector3d rO;
    Vector3d rOC;
    Matrix3d RO;

    Vector3d vO;
    Vector3d vOC;
    Vector3d wO;
    Vector3d vOo;

    Vector3d p;
    Vector3d lC;

    MatrixXd MO;
    VectorXd cO;
    VectorXd gO;
    VectorXd bO;

    MatrixXd dMO;

    Vector3d fO;
    Vector3d nO;

    void initialize(const int&, RigidBodyModelInfo&);

    void readModel();
    void update();
  };
}

#endif // RIGIDBODYMODEL_HPP_
