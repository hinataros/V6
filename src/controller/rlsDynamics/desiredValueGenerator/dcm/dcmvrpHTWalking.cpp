/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::dcmvrpHTWalking(const double &t)
{
  if(debug) DEBUG;

  walking.setStartTime(tw0[dcmNum]);
  walking.setFinishTime(twf[dcmNum]);
  walking.setStartValue(rXpreDes);
  walking.setFinishValue(rXf);

  walking.htVRP(t);

  rXDes = walking.rXDes;
  drXDes = walking.drXDes;
}
