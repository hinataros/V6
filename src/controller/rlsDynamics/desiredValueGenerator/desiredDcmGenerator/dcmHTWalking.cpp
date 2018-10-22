/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::dcmHTWalking(const double &t)
{
  if(debug) DEBUG;

  walking.setStartTime(sequence[desiredDcmGeneratorNum].tw0);
  walking.setFinishTime(sequence[desiredDcmGeneratorNum].twf);
  walking.setStartValue(sequence[desiredDcmGeneratorNum].rXpreDes);
  walking.setFinishValue(sequence[desiredDcmGeneratorNum].rXf);

  walking.ht(t);

  rXDes = walking.rXDes;
  drXDes = walking.drXDes;
}
