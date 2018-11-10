/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::dcmHTWalking(const double &t)
{
  if(debug) DEBUG;

  walking.setStartTime(tw0[dcmNum]);
  walking.setFinishTime(twf[dcmNum]);
  walking.setStartValue(rXpreDes);
  walking.setFinishValue(rXf);

  // walking.setExtForce(cal_FDes.segment(12,3));

  walking.ht(t);

  rXDes = walking.rXDes;
  drXDes = walking.drXDes;

  // walking.extht(t);
  // walking.eht(t);

  // rXBarDes = walking.rXBarDes;
  // drXBarDes = walking.drXBarDes;
}
