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

    void initialize(Config&, Info&);
    void initialParameter(Config&, Info&, Model&);

    void runge4(Config&, Info&, Model&, Controller&, Output&);

    void linkEqs(Config&, Info&, Model&, Controller&, Output&);
    void linkEqs(Config&, Info&, Model&, Controller&);
    void diffEqs(Config&, Info&, Model&, int);

    void integrator(Config&, Model&, int, double);
    void update(Config&, Info&, Model&);
    void se3exp(Config&, Vector3d&, Matrix3d&, Vector3d, Vector3d, double);

    void finalize(Config&, Info&, Model&, Controller&, Output&);
  public:
    void run(Config&, Info&, Model&, Controller&, Output&);

    RlsSimulator(Config &config, Info &info){
      initialize(config, info);
    }
  };
}
