/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readCnoid()
{
  if(debug) DEBUG;

  int worldItem = 0;
  int bodyItem;
  bool bodyFlag = false;

  struct stat statFile;
  if(stat(include_ic.path.c_str(), &statFile)!=0)
    cout << manip_error("TreeModel::readCnoid() error...") << endl
         << manip_error("no such file '"+include_ic.path+"'") << endl;

  YAML::Node doc = YAML::LoadFile(include_ic.path.c_str());

  int num = doc["items"]["children"][worldItem]["children"].size();
  // smiyahara: model parameterでincludeしたかどうかのflagが必要
  if(include_mp.path != ""){
    for(int i=0; i<num; i++){
      if(doc["items"]["children"][worldItem]["children"][i]["name"].as<string>()==info->name){
        bodyFlag = true;
        bodyItem = i;
      }
    }

    if(!bodyFlag)
      cout << manip_error("TreeModel::readCnoid() error...") << endl
           << manip_error("not found '"+info->name+"' item") << endl;
  }

  for(int i=0, k=0; i<3; i++){
    link[info->rootNode].r0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootPosition"][i].as<double>();

    for(int j=0; j<3; j++, k++)
      link[info->rootNode].R0(i,j) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootAttitude"][k].as<double>();

    try{
      link[info->rootNode].v0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootVelocity"][i].as<double>();

    }catch(...){link[info->rootNode].v0(i) = 0.;}

    try{
      link[info->rootNode].w0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootAngularVelocity"][i].as<double>();
    }catch(...){link[info->rootNode].w0(i) = 0.;}
  }

  link[info->rootNode].vo0 =
    link[info->rootNode].v0 + cross(link[info->rootNode].r0)*link[info->rootNode].w0;

  for(int i=0, j=0; i<info->linkNum; i++){
    if(link[i].active){
      link[i].th0 = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialJointPositions"][j].as<double>();

      try{
        link[i].dth0 = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialJointVelocities"][j].as<double>();
      }catch(...){}

      j++;
    }
  }
}
