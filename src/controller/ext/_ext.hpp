/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  class Ext{
  private:
    // // control method
    // // ******************************
    // // operational space controller
    // void relativeAccelerationCentroidalMap();

    // // configuration space acceleration controller
    // VectorXd centroidalAccelerationSynergy();

    // // momentum controller
    // void centroidalCmpMomentum();

    // // internal force controller
    // void m_internalDistribution();

    // // force controller
    // void baseDistribution();

    // // torque controller
    // void crb();

    // // inverse dynamics controller
    // VectorXd fullDynamicsController();

    // // external wrench controller
    // void transformExternalWrench();

  public:
    void setControllerMap(RlsDynamics*);
  };
}
