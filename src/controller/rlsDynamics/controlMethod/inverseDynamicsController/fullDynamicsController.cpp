#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::fullDynamicsController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // acceleration control
  (this->*motionController_ptr)(config, info, model);

  // momentum control
  (this->*momentumController_ptr)(config, info, model);

  // force control
  (this->*forceController_ptr)(config, info, model);

  // torque control
  (this->*torqueController_ptr)(config, info, model);

  return tau;
}
