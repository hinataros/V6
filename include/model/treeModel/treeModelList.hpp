#ifndef TREEMODELLIST_HPP_
#define TREEMODELLIST_HPP_

namespace RLS{
  class TreeModelList{
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

    MatrixXd eePosMatrix;
    MatrixXd eeOrientMatrix;
    MatrixXd eeVelMatrix;
    MatrixXd eeAngVelMatrix;

    // smiyahara: 一つにまとめるのはびみょ
    MatrixXd posGifMatrix;
  };
}

#endif // TREEMODELLIST_HPP_
