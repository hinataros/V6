/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::sequenceTrigger(const double &t, const struct State &state)
{
  if(debug) DEBUG;

  if(sequence[state.sequenceID].phase < 0) // for reset
    return 0;

  int tint = round_cast(t, 3);
  int tsumint = round_cast(sequence[state.sequenceID].twf, 3) + round_cast(sequence[state.sequenceID].tw0, 3);

  if(tint==tsumint)
    return sequence[state.sequenceID].phase + 1;

  return sequence[state.sequenceID].phase;
}
