/**
   @author Sho Miyahara 2017
*/

#include "common.hpp"
#include "world.hpp"

#include "treeModelList.hpp"

namespace RLS{
  class TreeModel:
    public World,
    virtual public Common{
  private:
    void joints();
    void initializeInfo();
    void initializeLink();
    void initializeAll();

    // kinematics
    void position();
    void velocity();

    // dynamics
    VectorXd recursiveNewtonEuler();
    VectorXd gravity();
    void identityVectorMethod();

    void analyticalDynamics();

    void outputConfig();

  public:
    struct Dof{
      int all;
      int root;
      int joint;
    };

    // smiyahara: 良い名前が浮かばなかった
    struct Each{
      int all;
      int axis[6];
    };
    // smiyahara: 別の名前希望
    struct Contact{
      string name;
      int num;
      Each c;
      Each m;
    };

    struct ChoModel{
      string body;
      string cnoid;
    };

    struct Info{
      bool dynamics_flag;
      string bodyName;
      string cnoidName;
      ChoModel name;
      ChoModel path;

      int rootNode;
      int linkNum;
      int controlNodeNum;
      Contact *controlNode;
      int sensorNodeNum;
      Contact *sensorNode;
      Dof dof;
      Contact contact;
    } info;

    struct All{ // smiyahara:ココのallの定義の仕方がびみょ
      double m;
      Vector3d rC;
      Vector3d vC;

      Vector3d p;
      Vector3d lC;

      MatrixXd Rk;
      MatrixXd dRk;
      MatrixXd TB2k;
      MatrixXd dTB2k;
      MatrixXd TC2k;
      MatrixXd dTC2k;
      MatrixXd J;
      MatrixXd dJ;

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

    struct Link{
      bool active;
      string name;
      string parent;
      int parentNode;
      string jointType;
      string jointAxis;
      // string linkType;

      // inital value
      Matrix3d R0;
      Vector3d r0;
      Vector3d w0;
      Vector3d vo0;
      Vector3d v0;// 今のところcnoidから読むとき、B部のみが必要
      double th0;
      double dth0;

      // joint value
      double th;
      double dth;

      Vector3d d;
      Vector3d ri2C;

      Vector3d ej;
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

      // for CoM jacobian
      MatrixXd Jvi;
      MatrixXd Jwi;
      MatrixXd dJvi;
      MatrixXd dJwi;

      // for recursive newton euler
      Vector3d dv_rne;
      Vector3d dw_rne;
      Vector3d dvC_rne;
      double ddth_rne;
      Vector3d fHat_rne;
      Vector3d nHat_rne;
      Vector3d f_rne;
      Vector3d n_rne;
      double tau_rne;
    } *link;

    TreeModelList tm_list;

    VectorXd readJointStateVector(string);
    void writeJointStateVector(string, VectorXd);
    VectorXd readSensorNodeValueVector(string);
    void writeSensorNodeValueVector(string, VectorXd);
    MatrixXd stateMatrixFilter(bool, bool, MatrixXd);
    VectorXd readControlNodeValueVector(string);

    void readModel(const string&);
    void setDir(const string&);
    void readBody();
    void readCnoid(Config::Clock&);
    void deleteModel();

    void transformMatrix();

    void update();
  };
}
