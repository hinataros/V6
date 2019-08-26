/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::comHTWalking(const double &t)
{
  if(debug) DEBUG;

  walking.setStartTime(tw0[comNum]);
  walking.setFinishTime(twf[comNum]);
  walking.setStartValue(rCpreDes);
  walking.setFinishValue(rCf);

  // rvrpCalc = 1;

  walking.htVRP(t);

  rCDes = walking.rCDes;
  vCDes = walking.drCDes;
  dvCDes = walking.ddrCDes;

  rXDes = walking.rXDes;
  drXDes = walking.drXDes;
}
