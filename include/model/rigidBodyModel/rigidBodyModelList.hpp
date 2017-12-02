#ifndef RIGIDBODYMODELLIST_HPP_
#define RIGIDBODYMODELLIST_HPP_

namespace RLS{
  class RigidBodyModelList{
  public:
    Vector3d rB;
    Matrix3d RB;
    Vector3d xiB;
    Vector3d vB;
    Vector3d wB;

    VectorXd th;
    VectorXd dth;

    Vector3d rC;
    Vector3d vC;

    Vector3d p;
    Vector3d lC;
  };
}

#endif // RIGIDBODYMODELLIST_HPP_
