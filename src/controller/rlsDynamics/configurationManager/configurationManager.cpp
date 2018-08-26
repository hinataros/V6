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

  // if(config.controller.driven=="event"||config.controller.driven=="mix"){
  //   // １ステップ目は初期化
  //   int temp=stateTriggerConfig(config, info, model, t);
  //   if(temp!=info.sim.state){
  //     info.sim.state=temp;
  //     flag = resetState(config, info, model, t);
  //   }
  // }

  if(config.controller.driven=="flow"||config.controller.driven=="mix"){
    for(int i=0; i<seqNum; i++){
      flag = sequenceTriggerConfig(t, config.clock.tf, i);

      if(flag){
        updateSequence(t, i);
        readWork(config.dir.work, "Sequence", i, model.hoap2.info.eeNum);
        sequence[i].phase++;
      }
    }
  }

  if(flag)
    mapping();

  return flag;
}
