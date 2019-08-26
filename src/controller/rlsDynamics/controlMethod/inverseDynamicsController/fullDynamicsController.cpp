/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::fullDynamicsController()
{
  if(debug) DEBUG;

  // momentum control
  if(!extMomentumController)
    (this->*momentumController_ptr)();
  else
    (ext->*ext_momentumController_ptr)(this);

  // motion control
  if(!extMotionController)
    (this->*motionController_ptr)();
  else
    (ext->*ext_motionController_ptr)(this);

  // force control
  if(!extForceController)
    (this->*forceController_ptr)();
  else
    (ext->*ext_forceController_ptr)(this);
  // o(cal_FcBarRef);

  // torque control
  if(!extTorqueController)
    (this->*torqueController_ptr)();
  else
    (ext->*ext_torqueController_ptr)(this);

  // o(cal_dVmBarRef);
  // o(ddqMoptRef);
  // o(cal_FcBarRef);
  // o(tau);

  return tau;
}
