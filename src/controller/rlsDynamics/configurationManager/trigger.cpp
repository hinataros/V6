/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::stateTrigger(const double &t)
{
  return (this->*customTrigger_ptr)(t);
}

bool RLS::RlsDynamics::sequenceTrigger(const double &t, const int &sequenceNum)
{
  int tint = round_cast(t, 3);
  int tfint = round_cast(worldModel->tf, 3);
  int tsumint = round_cast(sequence[sequenceNum].twf, 3) + round_cast(sequence[sequenceNum].tw0, 3);

  if(tint==tsumint&&tint<=tfint)
    return true;

  return false;
}
