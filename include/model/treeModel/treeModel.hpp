/**
   @author Sho Miyahara 2018
*/

#ifndef TREEMODEL_HPP_
#define TREEMODEL_HPP_

#include "yaml-cpp/yaml.h"
#include "common.hpp"

#include "info.hpp"
#include "worldModel.hpp"

#include "treeModelList.hpp"

namespace RLS{
  class TreeModel:
    virtual public Common{
  private:
    YAML::Node doc_treeModel;

    TreeModelInfo *info;
    WorldModel *worldModel;

    int uniqueNum;
    bool dynamics_flag;

    struct Include{
      string type;
      string search;
      string read;
      string path;
    } include_mp, include_ic;;

    void resizeLink();
    void resizeAll();

    void readBody();
    void readCnoid();

    void setModelParameterInclude(const string&);
    void setInitialConfigurationInclude(const string&);

    // kinematics
    void joints();
    void position();
    void velocity();

    // dynamics
    VectorXd recursiveNewtonEuler();
    VectorXd gravity();
    void identityVectorMethod();

    void analyticalDynamics();

    void outputConfig();

  public:
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

    TreeModelList outputList;

    VectorXd readJointStateVector(string);
    void writeJointStateVector(string, VectorXd);
    VectorXd readSensorNodeValueVector(string);
    void writeSensorNodeValueVector(string, VectorXd);
    MatrixXd stateMatrixFilter(bool, bool, MatrixXd);
    VectorXd readControlNodeValueVector(string);

    void initialize(const int&, TreeModelInfo&, WorldModel&);
    void finalize();

    void readModel(const string&, const string&);

    void transformMatrix();

    void update();

    TreeModel(){}
  };
}

#endif // TREEMODEL_HPP_
