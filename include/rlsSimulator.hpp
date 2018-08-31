/**
   @author Sho Miyahara 2017
*/

#include "common.hpp"

namespace RLS{
  class RlsSimulator:
    virtual public Common{
  private:
  public:
    double t;

    Vector3d rB;
    Matrix3d RB;
    Vector3d voB;
    Vector3d wB;

    VectorXd th;
    VectorXd dth;

    VectorXd u;

    Vector3d dvoB;
    Vector3d dwB;
    VectorXd ddth;

    struct K{
      Vector3d vo[4];
      Vector3d w[4];
      VectorXd dth[4];

      Vector3d dvo[4];
      Vector3d dw[4];
      VectorXd ddth[4];
    } k;

    void initialize(const TreeModel::Info&);
    void initialParameter(const Config::Clock&, TreeModel&);

    void runge4(Config&, Model&, RlsDynamics&, Output&);

    void linkEqs(Config&, Model&, RlsDynamics&, Output&);
    void linkEqs(Config&, Model&, RlsDynamics&);
    void diffEqs(Config&, Model&, const int);

    void integrator(Model&, const int, const double);
    void se3exp(Vector3d&, Matrix3d&, const Vector3d, const Vector3d, const double);
    void update(const Config::Clock&);

    void finalize(Model&, RlsDynamics&, Output&);
  public:
    void run(Config&, Model&, RlsDynamics&, Output&);

    RlsSimulator(const TreeModel::Info &info){
      initialize(info);
    }
  };
}
