#include "common.hpp"
#include "world.hpp"

#include "treeModelList.hpp"

namespace RLS{
  class TreeModel:
    public World,
    virtual public Common{
  private:
    void joints(Config&, Info&);
    void initialize(Config&, Info&);

    // kinematics
    void position(Config&, Info&, Vector3d, Matrix3d, VectorXd);
    void velocity(Config&, Info&, Vector3d, Vector3d, VectorXd);
    void jacobian(Config&, Info&);
    void diffJacobian(Config&, Info&);

    // dynamics
    VectorXd recursiveNewtonEuler(Config&, Info&, Vector3d, Vector3d, VectorXd);
    VectorXd gravity(Config&, Info&);
    void identityVectorMethod(Config&, Info&);

    void analyticalDynamics(Config&, Info&);

    void outputConfig(Config&, Info&);

  public:
    struct All{ // smiyahara:ココのallの定義の仕方がびみょ
      // state vector
      VectorXd th;
      VectorXd dth;

      double m;
      Vector3d rC;
      Vector3d vC;

      Vector3d p;
      Vector3d lC;

      MatrixXd M;
      VectorXd c;
      VectorXd g;
      VectorXd b;

      MatrixXd dM;

      MatrixXd JB2C;
      MatrixXd dJB2C;
      MatrixXd MM;
      MatrixXd dMM;
    } all;

    struct Node{
      string jointType;

      // inital value
      Vector3d xi0;
      Vector3d r0;
      Vector3d w0;
      Vector3d v0;// 今のところyamlから読むとき、B部のみが必要
      double th0;
      double dth0;

      Vector3d d;
      Vector3d ri2C;

      Vector6d jS;
      Vector3d sv;
      Vector3d sw;

      // momentと競合するから
      double m;
      Matrix3d Iw_C;
      Matrix3d I;

      Vector3d r;
      Vector3d rC;
      Matrix3d R;

      Vector3d v;
      Vector3d vC;
      Vector3d w;
      Vector3d vo;

      Vector3d dsv;
      Vector3d dsw;

      Matrix3d ISvv;
      Matrix3d ISvw;
      Matrix3d ISww;

      Vector3d p;
      Vector3d lC;

      // smiyahara: 初期接触力未定義
      Vector3d f;
      Vector3d n;

      // for recursive newton euler
      Vector3d dv_rne;
      Vector3d dw_rne;
      Vector3d dvC_rne;
      Vector3d fHat_rne;
      Vector3d nHat_rne;
      Vector3d f_rne;
      Vector3d n_rne;
    };

    struct Limb{
      MatrixXd J;
      MatrixXd dJ;

      Node *node;
    } *limb;

    TreeModelList tm_list;

    void readModel(Config&, Info&);
    void deleteModel(Config&, Info&);
    void update(Config&, Info&);
  };
}
