/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

bool RLS::RlsDynamics::stateTrigger(const double &t, struct State &state)
{
  if(debug) DEBUG;

  bool reset_flag = false;
  int tempCondition;

  string noKey = "none";
  string stateKey = "state";
  string sequenceKey = "sequence";
  yamlInfo.key = "state";

  // if(state.doc["test"])
  //   cout << "triggering: " << state.doc["test"].as<string>() << endl;

  if(state.trigger != noKey) {
    if(state.ext)
      tempCondition = (ext->*ext_stateTrigger_map[state.trigger])(this, t);
    else{
      tempCondition = (this->*stateTrigger_map[state.trigger])(t, state);
    }

    if(state.condition != tempCondition){
      // o("kirikaeing");
      // o(state.trigger);
      // o(state.fork);
      // o(tempCondition);
      // if(state.doc["test"])
      //   cout << "loading: " << state.doc["test"].as<string>() << endl;
      if(state.trigger == sequenceKey && tempCondition >= state.fork)
        tempCondition = state.fork-1; // 最後のsequenceを繰り返し

      // state reset
      if(state.doc[stateKey][tempCondition]["reset"]){ // 0位置の更新
        controllerModel.originReset(rkk);
        des.setInitialBoundary();
        des.updatePres();
        if(state.st_ptr_in[tempCondition].trigger == sequenceKey){
          sequence[state.st_ptr_in[tempCondition].sequenceID].phase = -1;
          // o("seq");
        }
        // o("resetshitayo!");
        // gc;
      }

      for(int i=0; i<state.fork; i++)
        state.st_ptr_in[i].condition = -1;
      if(state.st_ptr_in[tempCondition].fork){
        // cout << "resetting: " << state.doc["test"].as<string>() << " triggering into >> " << tempCondition << endl;
        stateTrigger(t, state.st_ptr_in[tempCondition]);
      }

      if(state.trigger == sequenceKey){
        // o("seq reset");
        sequence[state.sequenceID].tw0 = t;
        sequence[state.sequenceID].phase = tempCondition;
        des.update(t, state.sequenceID);
        yamlInfo.sequence = state.sequenceID;
        yamlInfo.sequenceState = tempCondition;
        // for walking
        if(state.doc["walking"] && state.condition < 0){
          yamlInfo.reset(state.doc);
          des.resetWalking(t);
        }
      }
      else if(state.trigger == stateKey){
        des.update(t); // 現状何もやってないからいらない
        yamlInfo.sequence = -1;
      }
      ext->reset(this, t);
      // o("readController");

      yamlInfo.reset(state.st_ptr_in[tempCondition].doc);
      allReadController();
      // o("done!");

      reset_flag = true;

      state.condition = tempCondition;
      // gc;
    }
    else {
      if(state.st_ptr_in[tempCondition].fork){
        reset_flag = (stateTrigger(t, state.st_ptr_in[tempCondition]) || reset_flag);
      }
    }
  }
  else if(state.fork){
    for(int i=0; i<state.fork; i++){
      bool rsftemp = stateTrigger(t, state.st_ptr_in[i]);
      reset_flag = (reset_flag || rsftemp);
    }
  }

  // cout << "returnnig...: " << state.doc["test"].as<string>() << endl;;
  return reset_flag;
}
