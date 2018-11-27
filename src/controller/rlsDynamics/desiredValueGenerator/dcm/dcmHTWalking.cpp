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

  // walking.ht(t);

  if(cal_FDes.segment(12,3).norm()==0.)
    walking.ht(t);
  else{
    walking.setExtForce(cal_FDes.segment(12,3));

    walking.eht(t);
  }

  rXDes = walking.rXDes;
  drXDes = walking.drXDes;
}
