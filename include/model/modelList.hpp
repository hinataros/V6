/**
   @author Sho Miyahara 2017
*/

namespace RLS{
  class ModelList{
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

    MatrixXd eePos;
    MatrixXd eeOrient;
    MatrixXd eeVel;
    MatrixXd eeAngVel;

    // smiyahara: 一つにまとめるのはびみょ
    MatrixXd posGif;
  };
}
