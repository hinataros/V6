/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

bool RLS::RlsDynamics::configurationManager(const Config &config, Model &model, double &t)
{
  if(debug) DEBUG;

  bool flag = false;

  if(config.controller.driven=="event"||config.controller.driven=="mix"){
    // １ステップ目は初期化
    int temp = stateTrigger(model, t);
    if(temp!=state.num){
      state.num = temp;

      updateState(model, t);
      readWork(config.dir.work, model.hoap2.info, false, "State", 0, state.num);

      flag = true;
    }
  }

  if(config.controller.driven=="flow"||config.controller.driven=="mix"){
    for(int i=0; i<seqNum; i++){
      flag = sequenceTrigger(t, config.clock.tf, i);

      if(flag){
        updateSequence(t, i);
        readWork(config.dir.work, model.hoap2.info, multiSequence, "Sequence", i, sequence[i].phase);
        sequence[i].phase++;
      }
    }
  }

  if(flag)
    mapping(model.hoap2.info.controlNodeNum);

  return flag;
}
