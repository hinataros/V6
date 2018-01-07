/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

bool RLS::RlsDynamics::configurationManager(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  bool flag = false;

  if(config.controller.driven=="event"||config.controller.driven=="mix"){
    // １ステップ目は初期化
    int temp=stateTriggerConfig(config, info, model, t);
    if(temp!=info.sim.state){
      info.sim.state=temp;
      flag = resetState(config, info, model, t);
    }
  }

  if(config.controller.driven=="flow"||config.controller.driven=="mix")
    if(sequenceTriggerConfig(config, info, t))
      flag = resetSequence(config, info, t);

  if(flag)
    mapping(config);

  return flag;
}
