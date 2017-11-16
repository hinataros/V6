#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::control(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.input=="velocity"||
     config.controller.input=="acceleration")
    input = (this->*mc_ptr)(config, info, model);

  else if(config.controller.input=="torque")
    input = (this->*tc_ptr)(config, info, model);

  else
    cout << "no such control input..." << endl;
}
