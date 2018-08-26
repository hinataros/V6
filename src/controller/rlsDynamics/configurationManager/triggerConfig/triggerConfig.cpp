/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

// int RLS::RlsDynamics::stateTriggerConfig(Config &config, Info &info, Model &model, double &t)
// {
//   // return 0;
//   return walkHT(config, info, model, t);
//   // return walking(config, info, model, t);
//   // return staticCheckContact(config, info, model, t);
//   // return ankleStratagy(config, info, model, t);
//   // return ankleHipStratagy(config, info, model, t);
// }

bool RLS::RlsDynamics::sequenceTriggerConfig(const double &t, const double tf, const int num)
{
  int tint = round_cast(t, 3);
  int tfint = round_cast(tf, 3);
  int tsumint = round_cast(sequence[num].twf, 3) + round_cast(sequence[num].tw0, 3);

  if(tint==tsumint&&tint<=tfint)
    return true;

  return false;
}
