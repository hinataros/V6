/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readModel(const string &dir_share, const string &path_yaml_model)
{
  if(debug) DEBUG;

  string treeModelKeyName = "tree model";

  string modelParameterKeyName = "model parameter";
  string initialConfigurationKeyName = "initial configuration";

  struct stat statFile;
  if(stat(path_yaml_model.c_str(), &statFile)!=0)
    cout << manip_error("TreeModel::readModel() error...") << endl
         << manip_error("no such file '"+path_yaml_model+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_model.c_str());

  if(!doc[treeModelKeyName][uniqueNum])
    doc_treeModel = doc[treeModelKeyName];
  else
    doc_treeModel = doc[treeModelKeyName][uniqueNum];

  info->name = doc_treeModel["name"].as<string>();
  dynamics_flag = doc_treeModel["dynamics calculation"].as<bool>();

  // smiyahara: エラー処理実装が億劫
  if(doc_treeModel[modelParameterKeyName]["include"]){
    include_mp.type = doc_treeModel[modelParameterKeyName]["include"]["type"].as<string>();
    include_mp.search = doc_treeModel[modelParameterKeyName]["include"]["search"].as<string>();
    include_mp.read = doc_treeModel[modelParameterKeyName]["include"]["path"].as<string>();

    setModelParameterInclude(dir_share);

    if(include_mp.type == "body")
      readBody();
  }
  else{
    cout << manip_error("TreeModel::readModel() error...") << endl
         << manip_error("not yet") << endl;
  }

  if(doc_treeModel[initialConfigurationKeyName]["include"]){
    include_ic.type = doc_treeModel[initialConfigurationKeyName]["include"]["type"].as<string>();
    include_ic.search = doc_treeModel[initialConfigurationKeyName]["include"]["search"].as<string>();
    include_ic.read = doc_treeModel[initialConfigurationKeyName]["include"]["path"].as<string>();

    setInitialConfigurationInclude(dir_share);

    if(include_ic.type == "cnoid")
      readCnoid();
  }
  else{
    cout << manip_error("TreeModel::readModel() error...") << endl
         << manip_error("not yet") << endl;
  }

  info->controlNodeNum = doc[treeModelKeyName]["control node"].size();
  info->controlNode = new ID[info->controlNodeNum];

  for(int i=0; i<info->controlNodeNum; i++){
    info->controlNode[i].name = doc[treeModelKeyName]["control node"][i].as<string>();
    info->controlNodeID[info->controlNode[i].name] = i;
  }

  for(int i=0; i<info->controlNodeNum; i++){
    bool flag = false;
    for(int j=0; j<info->linkNum; j++){
      if(link[j].name==info->controlNode[i].name){
        info->controlNode[i].num = j;
        flag = true;
      }
    }

    if(!flag){
      cout << manip_error("TreeModel::readBody() error...") << endl
           << manip_error("not found '"+info->controlNode[i].name+"' node") << endl;
      info->controlNode[i].num = 0;
    }
  }

  resizeAll();

  // smiyahara: 場所がびみょ～
  joints();
}
