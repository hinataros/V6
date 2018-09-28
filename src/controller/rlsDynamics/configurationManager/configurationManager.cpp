/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

bool RLS::RlsDynamics::configurationManager(const Config &config, const Model &model, const double &t)
{
  if(debug) DEBUG;

  bool flag_configuration=false, flag_state = false, flag_sequence = false;

  if(this->info.driven=="event"||this->info.driven=="mix"){
    // １ステップ目は初期化
    int temp = stateTrigger(model, t);
    if(temp!=state.num){
      state.num = temp;

      updateState(model, t);
      readWork(model.hoap2.info, false, "State", 0, state.num);

      flag_state = true;
    }
  }

  if(this->info.driven=="flow"||this->info.driven=="mix"){
    for(int i=0; i<seqNum; i++){
      flag_sequence = sequenceTrigger(t, config.clock.tf, i);

      if(flag_sequence){
        updateSequence(t, i);
        readWork(model.hoap2.info, multiSequence, "Sequence", i, sequence[i].phase);
        sequence[i].phase++;
      }
    }
  }

  if(flag_state||flag_sequence){
    mapping(model.hoap2.info.controlNodeNum);
    flag_configuration = true;
  }

  return flag_configuration;
}
