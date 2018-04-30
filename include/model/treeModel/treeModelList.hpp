/**
   @author Sho Miyahara 2017
*/

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

    VectorXd r;
    VectorXd xi;

    VectorXd v;
    VectorXd w;

    VectorXd f;
    VectorXd n;

    Vector3d p;
    Vector3d lC;

    // smiyahara: 一つにまとめるのはびみょ
    MatrixXd posGifMatrix;
  };
}

#endif // TREEMODELLIST_HPP_
