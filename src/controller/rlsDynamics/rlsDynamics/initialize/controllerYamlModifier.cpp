// amiyata
// v5.1.0までのcontroller yamlのための対応 書きやすくなるという利点もある

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"


void RLS::RlsDynamics::controllerYamlModifier(YAML::Node &doc)
{
  if(debug) DEBUG;

  string stateKey = "state";
  string sequenceKey = "sequence";
  string triggerKey = "trigger";
  string extTriggerKey = "ext trigger";

  string walkingKey = "walking";


  YAML::Node temp;
  if(doc[stateKey] && doc[sequenceKey]){
    temp = doc;
    doc.remove(doc[stateKey]);
    doc.remove(doc[sequenceKey]);

    doc[stateKey][0][stateKey] = temp[stateKey];
    if(doc[triggerKey])
      doc[stateKey][0][triggerKey] = temp[triggerKey];
    if(doc[extTriggerKey])
      doc[stateKey][0][extTriggerKey] = temp[extTriggerKey];
    doc[stateKey][1][sequenceKey] = temp[sequenceKey];
    if(doc[walkingKey]){
      doc.remove(doc[walkingKey]);
      doc[stateKey][1][walkingKey] = temp[walkingKey];
    }
  }
  else if(doc[sequenceKey][0][0]){
    for(int i=0; i<(signed int)doc[sequenceKey][0].size(); i++){
      temp = doc[sequenceKey];
      doc.remove(doc[sequenceKey]);

      doc[stateKey][i][sequenceKey] = temp[sequenceKey][i];
    }
  }

  if(doc[stateKey]){
    o(doc[stateKey].size());
    for(int i=0; i<(signed int)doc[stateKey].size(); i++){
      o(i);
      gc;
      temp = doc[stateKey][i];
      controllerYamlModifier(temp);
      doc.remove(doc[stateKey][i]);
      doc[stateKey][i] = temp;
    }
  }
  if(doc[sequenceKey]){
    o(doc[sequenceKey].size());
    for(int i=0; i<(signed int)doc[sequenceKey].size(); i++){
      o(i);
      gc;
      temp = doc[sequenceKey][i];
      controllerYamlModifier(temp);
      doc.remove(doc[sequenceKey][i]);
      doc[sequenceKey][i] = temp;
    }
  }
}
