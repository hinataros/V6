/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

bool RLS::RlsDynamics::configurationManager(const string driven, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  bool flag = false;

  // if(config.controller.driven=="event"||config.controller.driven=="mix"){
  //   // １ステップ目は初期化
  //   int temp=stateTriggerConfig(config, info, model, t);
  //   if(temp!=info.sim.state){
  //     info.sim.state=temp;
  //     flag = resetState(config, info, model, t);
  //   }
  // }

  if(driven=="flow"||driven=="mix")
    if(sequenceTriggerConfig(config, info, t))
      flag = resetSequence(config, info, t);

  if(flag)
    mapping(config);

  return flag;
}
