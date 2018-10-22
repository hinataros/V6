/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::initializeWalking()
{
  if(debug) DEBUG;

  walking.setModel(*model);
  walking.setYamlInfo(*yamlInfo);
  walking.initialize();

  walking.setInitialDcmPosition(model->rX0);
  walking.setComPosition(model->rC0);

  walking.createHTTrajectory();
}
