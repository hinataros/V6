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

  if(configurationManager(t))
    reconfigure();

  update();

  des.desiredValueGenerator(t);
  fb.feedbackController();
  ext->trajectoryGenerator(this, t);

  controlMethod();

  outputConfig();

  return input;
}
