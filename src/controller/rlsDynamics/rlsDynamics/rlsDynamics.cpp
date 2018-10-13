/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::rlsDynamics(const double &t)
{
  if(debug) DEBUG;

  controllerModel.update();

  if(configurationManager(t))
    reconfigure();

  update();

  des.desiredValueGenerator(t);
  fb.feedbackController();

  controlMethod();

  outputConfig();

  return input;
}
