/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_extList.hpp"

namespace RLS{
  class Ext:
    public Interpolation{
  private:
    double tw0;
    double twf;

    Vector3d des;

    Vector3d hoge0;
    Vector3d hogepreDes;
    Vector3d hogef;

    Vector3d hogeDes;
    Vector3d dhogeDes;
    Vector3d ddhogeDes;

    // // control method
    // // ******************************
    // motion controller
    VectorXd testMotionController(RlsDynamics*);

    // momentum controller
    void testMomentumController(RlsDynamics*);

    // force controller
    void testForceController(RlsDynamics*);

    // torque controller
    void testTorqueController(RlsDynamics*);

    // inverse dynamics controller
    VectorXd testInverseDynamicsController(RlsDynamics*);

    // // external wrench controller
    // void testExternalWrenchController(RlsDynamics*);

  public:
    ExtList outputList;

    void defaultController(RlsDynamics*);
    VectorXd defaultJointController(RlsDynamics*);
    VectorXd defaultConfigurationController(RlsDynamics*);

    void initialize(RlsDynamics*);
    void reset(RlsDynamics*, const double&);
    void readController(RlsDynamics*);
    void reconfigure(RlsDynamics*);
    void every(RlsDynamics*, const double&);
    void output(RlsDynamics*);
    void finalize(RlsDynamics*);
  };
}
