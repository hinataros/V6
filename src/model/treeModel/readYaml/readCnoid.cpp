/**
   @author Sho Miyahara 2017
*/

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readCnoid(Config::Clock &clock)
{
  if(debug) DEBUG;

  int worldItem = 0;
  int bodyItem, aistItem;
  bool bodyFlag=false, aistFlag=false;

  YAML::Node doc = YAML::LoadFile(info.path.cnoid.c_str());

  clock.t0 = doc["toolbars"]["TimeBar"]["minTime"].as<double>();
  clock.tf = doc["toolbars"]["TimeBar"]["maxTime"].as<double>();
  clock.dt = 1./doc["toolbars"]["TimeBar"]["frameRate"].as<int>();
  clock.n = (clock.tf - clock.t0)/clock.dt;

  int num = doc["items"]["children"][worldItem]["children"].size();
  for(int i=0; i<num; i++){
    if(doc["items"]["children"][worldItem]["children"][i]["name"].as<string>()==info.name.body){
      bodyFlag=true;
      bodyItem = i;
    }

    if(doc["items"]["children"][worldItem]["children"][i]["name"].as<string>()=="AISTSimulator"){
      aistFlag=true;
      aistItem = i;
    }
  }

  if(!bodyFlag)
    cout << "****************************************************************" << endl
         << "not found '" << info.name.body << "' item" << endl
         << "****************************************************************" << endl;
  if(!aistFlag)
    cout << "not found 'AISTSimulator' item" << endl;

  for(int i=0; i<3; i++)
    try{
      ag(i) = doc["items"]["children"][worldItem]["children"][aistItem]["data"]["gravity"][i].as<double>();
    }catch(...){ag(i) = 0.;}

  for(int i=0, k=0; i<3; i++){
    link[info.rootNode].r0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootPosition"][i].as<double>();

    for(int j=0; j<3; j++, k++)
      link[info.rootNode].R0(i,j) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootAttitude"][k].as<double>();

    try{
      link[info.rootNode].v0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootVelocity"][i].as<double>();

    }catch(...){link[info.rootNode].v0(i) = 0.;}

    try{
      link[info.rootNode].w0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootAngularVelocity"][i].as<double>();
    }catch(...){link[info.rootNode].w0(i) = 0.;}
  }

  link[info.rootNode].vo0 =
    link[info.rootNode].v0 + cross(link[info.rootNode].r0)*link[info.rootNode].w0;

  for(int i=0, j=0; i<info.linkNum; i++){
    if(link[i].active){
      link[i].th0 = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialJointPositions"][j].as<double>();

      try{
        link[i].dth0 = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialJointVelocities"][j].as<double>();
      }catch(...){}

      j++;
    }
  }
}
