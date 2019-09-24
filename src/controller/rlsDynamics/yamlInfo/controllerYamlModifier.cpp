// amiyata
// v5.1.0までのcontroller yamlのための対応 書きやすくなるという利点もある

#include "config.hpp"
#include "yamlInfo.hpp"


void RLS::YamlInfo::controllerYamlModifier(YAML::Node doc)
{
  if(debug) DEBUG;

  YAML::Node temp;

  string stateKey = "state";
  string sequenceKey = "sequence";
  string triggerKey = "trigger";
  string extTriggerKey = "ext trigger";
  string walkingKey = "walking";

  if(doc[stateKey] && doc[sequenceKey]){
    temp = YAML::Clone(doc);
    // delete existing states
    doc.remove(stateKey);
    doc.remove(sequenceKey);

    // copy state to fork[0]
    doc[stateKey][0][stateKey] = temp[stateKey];
    if(doc[triggerKey]){
      doc.remove(triggerKey);
      doc[stateKey][0][triggerKey] = temp[triggerKey];
    }
    if(doc[extTriggerKey]){
      doc.remove(extTriggerKey);
      doc[stateKey][0][extTriggerKey] = temp[extTriggerKey];
    }

    // copy sequence to fork[1]
    doc[stateKey][1][sequenceKey] = temp[sequenceKey];
    if(doc[walkingKey]){
      doc.remove(walkingKey);
      doc[stateKey][1][walkingKey] = temp[walkingKey];
    }
  }
  else if(doc[sequenceKey][0][0]){
    temp = YAML::Clone(doc[sequenceKey]);
    doc.remove(sequenceKey);

    if(doc[walkingKey]){ // 正直この状況は勘弁してほしいがとりあえず最初のsequenceに配置
      doc.remove(walkingKey);
      doc[stateKey][0][walkingKey] = temp[walkingKey];
    }
    for(int i=0; i<(signed int)temp.size(); i++)
      doc[stateKey][i][sequenceKey] = temp[i];

  }

  // recursive modifying
  if(doc[stateKey]){
    for(int i=0; i<(signed int)doc[stateKey].size(); i++){
      controllerYamlModifier(doc[stateKey][i]);
    }
  }
  else if(doc[sequenceKey]){
    for(int i=0; i<(signed int)doc[sequenceKey].size(); i++){
      controllerYamlModifier(doc[sequenceKey][i]);
    }
  }
}
