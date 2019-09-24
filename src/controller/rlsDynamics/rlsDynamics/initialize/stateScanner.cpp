// amiyata
// 2019/09/19 removeに関して YAML::Nodeはポインタなのでどこかで消すと他も消えるので注意

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"


void RLS::RlsDynamics::stateScanner(struct State &state)
{
  if(debug) DEBUG;

  string stateKey = "state";
  string sequenceKey = "sequence";
  string triggerKey = "trigger";
  string extTriggerKey = "ext trigger";

  state.trigger = "none";
  state.condition = -1000;
  state.stateID = -1;
  state.sequenceID = -1; // minus sequence doesnt exists
  state.finishSeq = false;
  state.ext = false;

  if(state.doc[triggerKey]){
    state.trigger = state.doc[triggerKey].as<string>();
    if(state.doc[extTriggerKey])
      state.ext = state.doc[extTriggerKey].as<bool>();

    if(!state.doc[stateKey]){
      cout << manip_error("state load error: trigger needs some state elements...") << endl;
      exit(-1);
    }
  }

  if(state.doc[stateKey]) {
    state.fork = state.doc[stateKey].size();
    state.stateID = stNum;
    stNum++;
    if(state.fork){
      // fork >= 1;
      state.st_ptr_in = new struct State[state.fork];
      for(int i=0; i<state.fork; i++) {
        state.st_ptr_in[i].doc = state.doc[stateKey][i];
        stateScanner(state.st_ptr_in[i]);
      }
      // state.doc.remove(stateKey); //余計なデータは消そーネ
    }
    else {
      state.st_ptr_in = new struct State[1];
      for(int i=0; i<state.fork; i++) {
        state.st_ptr_in[0].doc = state.doc[stateKey];
        // stateScanner(state.st_ptr_in[0]); // この状況は想定しない
      }
    }
  }
  else if(state.doc[sequenceKey]){
    state.trigger = sequenceKey;
    state.stateID = stNum;
    state.sequenceID = seqNum;
    // oss << "state: " << stNum << " & sequence: " << seqNum;
    // state.stateState = oss.str();
    stNum++;
    seqNum++;
    state.fork = state.doc[sequenceKey].size();
    if(!state.fork){
      cout << manip_error("state load error: no sequence elements!!") << endl;
      exit(-1);
    }
    state.st_ptr_in = new struct State[state.fork];
    for(int i=0; i<state.fork; i++) {
      state.st_ptr_in[i].doc = state.doc[sequenceKey][i];
      stateScanner(state.st_ptr_in[i]);
    }
    // state.doc.remove(sequenceKey); // 余計なデータは(ry
  }
  else {
    state.fork = 0;
    // state.doc.remove(); // 余(ry
  }
}


void RLS::RlsDynamics::statePrinter(struct State &state,int fork, int nest)
{
  int i;

  for(i=0; i<nest; i++)
    cout << "\t";
  if(state.stateID >= 0)
    cout << "\033[3" << (state.stateID+1) << "m" << "Here is state " << state.stateID << "\033[m" << endl;
  else
    cout << "Here is element " << fork << endl;
  if(state.trigger != "none"){
    for(i=0; i<nest; i++)
      cout << "\t";
    cout << "trigger: ";
    if(state.trigger=="sequence" && state.doc["walking"])
      cout << "walking ";
    cout << state.trigger;
    if(state.trigger=="sequence")
      cout << " " << state.sequenceID;
    cout << endl;
  }
  else if(state.fork){
    for(i=0; i<nest; i++)
      cout << "\t";
    cout << "forking states: " << endl;
  }

  for(i=0; i<state.fork; i++)
    statePrinter(state.st_ptr_in[i], i, nest+1);
}
