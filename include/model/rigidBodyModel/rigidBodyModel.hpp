/**
   @author Sho Miyahara 2018
*/

#ifndef RIGIDBODYMODEL_HPP_
#define RIGIDBODYMODEL_HPP_

#include "yaml-cpp/yaml.h"

#include "info.hpp"
#include "worldModel.hpp"

// #include "rigidBodyModelList.hpp"

namespace RLS{
  class RigidBodyModel{
  private:
    YAML::Node doc_rigidBodyModel;

    RigidBodyModelInfo *info;
    WorldModel *worldModel;

    int uniqueNum;

    void resize();

  public:
    double m;
    Vector3d xiR0;
    Vector3d rR0;
    Vector3d wR0;
    Vector3d vR0;// 今のところyamlから読むとき、B部のみが必要

    Matrix3d Iw_C;
    Matrix3d I;

    Vector3d rR;
    Vector3d rC;
    Matrix3d RR;

    Vector3d vR;
    Vector3d vC;
    Vector3d wR;
    Vector3d vRo;

    Vector3d p;
    Vector3d lC;

    MatrixXd M;
    VectorXd c;
    VectorXd g;
    VectorXd b;

    MatrixXd dM;

    Vector3d fR;
    Vector3d nR;

    void initialize(const int&, RigidBodyModelInfo&, WorldModel&);

    void readModel(const string&, const string&);

    void update();
  };
}

#endif // RIGIDBODYMODEL_HPP_
