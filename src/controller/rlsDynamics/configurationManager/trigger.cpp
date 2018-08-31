/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::stateTrigger(Model &model, double &t)
{
  return (this->*customTrigger_ptr)(model, t);
}

bool RLS::RlsDynamics::sequenceTrigger(const double &t, const double tf, const int num)
{
  int tint = round_cast(t, 3);
  int tfint = round_cast(tf, 3);
  int tsumint = round_cast(sequence[num].twf, 3) + round_cast(sequence[num].tw0, 3);

  if(tint==tsumint&&tint<=tfint)
    return true;

  return false;
}
