/**
   @author Sho Miyahara 2017
*/

#include "common.hpp"

namespace RLS{
  class RlsSimulator:
    virtual public Common{
  private:
    struct Config{
      string *controlInput;
    } config;

    VectorXd *u;

    struct K{
      Vector3d vo[4];
      Vector3d w[4];
      VectorXd dth[4];

      Vector3d dvo[4];
      Vector3d dw[4];
      VectorXd ddth[4];
    } *k;

    Vector3d dvoB;
    Vector3d dwB;
    VectorXd ddth;

  public:
    double t;

    struct State{
      Vector3d rB;
      Matrix3d RB;
      Vector3d voB;
      Vector3d wB;

      VectorXd th;
      VectorXd dth;
    } *state;

    void initialize(const string&, const Info&);
    void initializeState(const Info&);
    void finalize();
    void readRlsSimulator(const string&, const Info&);
    void initialParameter(Model&);

    void setState2Model(Model&);
    void runge4(Model&, Controller&, Output&);

    void linkEqs(Model&, Controller&, Output&);
    void linkEqs(Model&, Controller&);
    void diffEqs(const int, Model&);

    void integrator(const int, const double, Model&);
    void se3exp(const int, Vector3d&, Matrix3d&, const Vector3d&, const Vector3d&, const double);
    void update(const Info&, const double);

  public:
    void run(Model&, Controller&, Output&);

    RlsSimulator(const string &path_yaml_rlsSimulator, const Info &info){
      initialize(path_yaml_rlsSimulator, info);
    }

    ~RlsSimulator(){
      finalize();
    }
  };
}
