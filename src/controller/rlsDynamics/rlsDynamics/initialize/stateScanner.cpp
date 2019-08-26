/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

// struct State{
//   struct State *st_ptr_in; // recursive state
//   int fork; // state nums
//   // string mode; // state or sequence
//   string trigger; // trigger config sellect
//   YAML::Node doc; // load whole of phase yaml
//   int condition; // current state num
//   int sequenceID; // sequence identifier for sequence trigger
// } topState;

void RLS::RlsDynamics::stateScanner(struct State &state)
{
  if(debug) DEBUG;

  string stateKey = "state";
  string sequenceKey = "sequence";
  string triggerKey = "trigger";
  string extTriggerKey = "trigger";

  state.trigger = "none";
  state.condition = -1000;
  state.sequenceID = -1; // minus sequence doesnt exists
  state.ext = false;

  if(state.doc[triggerKey]){
    state.trigger = state.doc[triggerKey].as<string>();
    if(!state.doc[stateKey]){
      cout << manip_error("state load error: trigger needs some state elements...") << endl;
      gc;
    }
  }
  else if(state.doc[extTriggerKey]){
    state.ext = true;
    state.trigger = state.doc[extTriggerKey].as<string>();
    if(!state.doc[stateKey]){
      cout << manip_error("state load error: trigger needs some state elements...") << endl;
      gc;
    }
  }

  if(state.doc[stateKey]) {
    state.fork = state.doc[stateKey].size();
    if(state.fork){
      // fork = 1;
      state.st_ptr_in = new struct State[state.fork];
      for(int i=0; i<state.fork; i++) {
        state.st_ptr_in[i].doc = state.doc[stateKey][i];
        stateScanner(state.st_ptr_in[i]);
      }
      state.doc.remove(state.doc[stateKey]); //余計なデータは消そーネ
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
    seqNum++;
    state.sequenceID = seqNum;
    state.fork = state.doc[sequenceKey].size();
    if(!state.fork){
      cout << "state load error: no sequence elements!!" << endl;
      gc;
    }
    state.st_ptr_in = new struct State[state.fork];
    for(int i=0; i<state.fork; i++) {
      state.st_ptr_in[i].doc = state.doc[sequenceKey][i];
      stateScanner(state.st_ptr_in[i]);
    }
    state.doc.remove(state.doc[sequenceKey]); //余計な(ry
  }
  else {
    state.fork = 0;
    state.doc.remove(state.doc);
  }
}


void RLS::RlsDynamics::statePrinter(struct State &state, int fork, int nest)
{
  int i;
  for(i=0; i<nest; i++)
    cout << "\t";
  cout << "Here is state " << fork << endl;
  if(state.trigger != "none"){
    for(i=0; i<nest; i++)
      cout << "\t";
    cout << "trigger: ";
    if(state.trigger=="sequence" && state.doc["walking"])
      cout << "walking ";
    cout << state.trigger << endl;
  }
  else if(state.fork){
    for(i=0; i<nest; i++)
      cout << "\t";
    cout << "forking states: " << endl;
  }

  for(i=0; i<state.fork; i++)
    statePrinter(state.st_ptr_in[i], i, nest+1);
}
