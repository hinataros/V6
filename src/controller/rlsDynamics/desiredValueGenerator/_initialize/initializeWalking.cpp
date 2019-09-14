/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::initializeWalking()
{
  if(debug) DEBUG;

  rvrpCalc = 0;

  walking.setModel(*model);
  // walking.initialize();
  //
  // walking.setInitialDcmPosition(model->rX0);
  // walking.setComPosition(model->rC0);
  // walking.setNaturalFrequency(model->wX);
  //
  // walking.setWayPoint(); //amiyata
  // walking.createHTTrajectory();
  // walking.createVRPTrajectory(); // amiyata
}

void RLS::DesiredValueGenerator::resetWalking(const double &t)
{
  if(debug) DEBUG;

  walking.resize();

  walking.setInitialDcmPosition(model->rX0);
  walking.setComPosition(model->rC0); // amiyata
  walking.setBaseRotation(model->RB0); // amiyata
  walking.setEEPosition(info->controlNodeNum, model->r0, model->R0); // amiyata
  walking.setNaturalFrequency(model->wX);

  walking.setInitialTime(t); // amiyata

  walking.initialize();

  walking.setWayPoint(); //amiyata
  walking.createHTTrajectory();
  if(walking.ToptimF)
    walking.createVRPTrajTopt(); // amiyata
  else
    walking.createVRPTrajectory(); // amiyata
}
