/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

bool RLS::RlsDynamics::configurationManager(const double &t)
{
  if(debug) DEBUG;

  bool flag_configuration=false, flag_state = false, flag_sequence = false;

  if(config.driven=="event"||config.driven=="mix"){
    // １ステップ目は初期化
    int temp = stateTrigger(t);

    if(temp!=state.num){
      state.num = temp;

      des.update(t);
      ext->reset(this, t);

      yamlInfo.reset(yamlInfo.stateKeyName, 0, state.num);
      allReadController();

      flag_state = true;
    }
  }

  if(config.driven=="flow"||config.driven=="mix"){
    for(int i=0; i<yamlInfo.sequenceNum; i++){
      if(sequenceTrigger(t, i)){
        sequence[i].tw0 = t;

        des.update(t, i);
        ext->reset(this, t);

        yamlInfo.reset(yamlInfo.sequenceKeyName, i, sequence[i].phase);
        allReadController();

        sequence[i].phase++;

        flag_sequence = true;
      }
    }
  }

  if(flag_state||flag_sequence){
    des.mapping();
    fb.mapping();
    mapping();

    flag_configuration = true;
  }

  return flag_configuration;
}
