/**
   @author Sho Miyahara 2018
*/

#include <iostream>
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/assign/list_of.hpp>

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_extList.hpp"

namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<double> point;
typedef bg::model::polygon<point> polygon;


namespace RLS{
  class Ext:
    public Interpolation{
  private:

  public:
    ExtList outputList;

    // state trigger
    // ******************************
    int defaultStateTrigger(RlsDynamics*, const double&);

    // control method
    // ******************************
    // motion controller
    VectorXd defaultConfigurationController(RlsDynamics*);
    VectorXd testMotionController(RlsDynamics*);
    VectorXd relativeAngularAcceleration(RlsDynamics*);
    VectorXd RAA_noDistribution(RlsDynamics*);
    VectorXd RAA_fullBase(RlsDynamics*);
    VectorXd RAA_partialBase(RlsDynamics*);
    VectorXd RAA_RNS(RlsDynamics*);
    VectorXd relativeAngularVelocity(RlsDynamics*);
    VectorXd RAV_noDistribution(RlsDynamics*);
    VectorXd RAV_fullBase(RlsDynamics*);
    VectorXd RAV_partialBase(RlsDynamics*);
    VectorXd RAV_noBase(RlsDynamics*);
    VectorXd resolvedMomentumControl(RlsDynamics*);
    VectorXd jointLimitAvoidance(RlsDynamics*, string);
    VectorXd jointLimitStop(RlsDynamics*, string);

    // momentum controller
    void testMomentumController(RlsDynamics*);
    void linear_CRB(RlsDynamics*);
    void linear_Damper(RlsDynamics*);
    void linear_RNS(RlsDynamics*);
    void linear_MobilityCompensation(RlsDynamics*);
    void linear_FrictionDistribution(RlsDynamics*);
    void vrp_CRB(RlsDynamics*);
    void vrp_Damper(RlsDynamics*);
    void vrp_RNS(RlsDynamics*);
    void vrp_MobilityCompensation(RlsDynamics*);
    void vrp_FrictionDistribution(RlsDynamics*);
    void vrp_FrictionDistribution_zDamper(RlsDynamics*);
    void vrp_FrictionDistribution_zRNS(RlsDynamics*);
    void CRB_AM(RlsDynamics*);
    void SAM_Damper(RlsDynamics*);
    void SAM_RNS(RlsDynamics*);
    void SAM_MobilityCompensation(RlsDynamics*);
    void SAM_FrictionDistribution(RlsDynamics*);
    void SAM_FrictionDistribution_zDamper(RlsDynamics*);
    void SAM_FrictionDistribution_zRNS(RlsDynamics*);

    // force controller
    void testForceController(RlsDynamics*);
    void copDistribution(RlsDynamics*);

    // torque controller
    void testTorqueController(RlsDynamics*);

    // inverse dynamics controller
    VectorXd defaultJointController(RlsDynamics*);
    VectorXd testInverseDynamicsController(RlsDynamics*);

    // // external wrench controller
    // void testExternalWrenchController(RlsDynamics*);

    // other
    void defaultController(RlsDynamics*);

    // variables
    // ******************************

    VectorXd h;
    VectorXd h2;
    VectorXd h3;

    VectorXd pMinus;
    VectorXd pPlus;

    Vector6d w_CRB;
    Vector6d w_CAM;
    Vector6d w_Sum;

    MatrixXd W;
    MatrixXd dW;

    Vector6d cal_VMRefBar;
    Vector6d cal_dVMRefBar;

    VectorXd dthMax;
    VectorXd dthMin;
    
    MatrixXd Jw;
    MatrixXd dJw;

    MatrixXd cal_JthM;
    MatrixXd cal_dJthM;

    VectorXd wC;
    
    VectorXd wCRef;
    VectorXd dwCRef;
    VectorXd DwRef;
    VectorXd dDwRef;

    // for gain scheduling
    
    bool impact;
    double t_impact;

    bool reflex;
    double t_reflex;

    MatrixXd KpwBinit;
    MatrixXd KdwBinit;

    double K;
    double dK;

    // base of support
    // ******************************
    void baseOfSupport(RlsDynamics*);
    bool floating;
    polygon Foot[2], BoS, BoSPre;
    

    // other function
    // ******************************
    void gainSchedule(RlsDynamics*, const double&);
    void kineticEnergy(RlsDynamics*, const double&);
    void forceEstimation(RlsDynamics*, const double&);

    void angularAccelerationDistribution(RlsDynamics*, bool);
    void RNSAccelerationDistribution(RlsDynamics*);
    void dampingDistribution(RlsDynamics*);
    void angularVelocityDistribution(RlsDynamics*, bool);
    void rootLinkManipulability(RlsDynamics*, Vector6d, string);
    void systemAngularMomentumLimitation(RlsDynamics*);
    void constraintCheck(RlsDynamics*);
    Vector2d nearPoint(Vector2d, polygon);
    
    void initialize(RlsDynamics*);
    void reset(RlsDynamics*, const double&);
    void readController(RlsDynamics*);
    void reconfigure(RlsDynamics*);
    void every(RlsDynamics*, const double&);
    void output(RlsDynamics*);
    void finalize(RlsDynamics*);
  };
}
