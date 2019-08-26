/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::continuousSequence(const double &t, const struct State &state)
{
  if(debug) DEBUG;

  string stateKeyName = "state";
  string sequenceKeyName = "sequence";

  if(state.condition >= 0){
    int tint = round_cast(t, 3);
    int tsumint = round_cast(sequence[state.st_ptr_in[state.condition].sequenceID].twf, 3) +
                  round_cast(sequence[state.st_ptr_in[state.condition].sequenceID].tw0, 3);

    int finishSeq = state.st_ptr_in[state.condition].doc[sequenceKeyName].size() - 1;

    if(tint==tsumint && sequence[state.st_ptr_in[state.condition].sequenceID].phase == finishSeq){
      if(state.doc[stateKeyName][state.condition]["jump"])
        return state.doc[stateKeyName][state.condition]["jump"].as<int>();
      else
        return state.condition + 1;
    }
  }
  else
   return 0; // 初期は0から

  return state.condition;
}
