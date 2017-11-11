#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::control(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(config.solver.input=="velocity")
    input = (this->*vc_ptr)(config, info, model);

  else if(config.solver.input=="acceleration")
    input = (this->*ac_ptr)(config, info, model);

  else if(config.solver.input=="torque"){
    (this->*ac_ptr)(config, info, model);
    momentumController(config, info, model);
    forceController(config, info, model);

    input = torqueController(config, info, model);
  }

  else
    cout << "no such control input..." << endl;
}
