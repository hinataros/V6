/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

VectorXd RLS::RlsDynamics::rlsDynamics(const double &t)
{
  if(debug) DEBUG;

  controllerModel.update();

  if(configurationManager(t)){
    constraintModel.reconfigure();
    reconfigure();
    ext->reconfigure(this);
  }

  constraintModel.update();

  des.desiredValueGenerator(t);
  fb.feedbackController();
  ext->every(this, t);

  controlMethod();

  outputConfig();

  return input;
}
