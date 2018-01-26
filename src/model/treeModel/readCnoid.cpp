/**
   @author Sho Miyahara 2017
*/

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readCnoid(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  int worldItem = 0;
  int bodyItem, aistItem;

  YAML::Node doc = YAML::LoadFile(config.dir.cnoid.c_str());

  info.sim.t0 = doc["toolbars"]["TimeBar"]["minTime"].as<double>();
  info.sim.tf = doc["toolbars"]["TimeBar"]["maxTime"].as<double>();
  info.sim.dt = 1./doc["toolbars"]["TimeBar"]["frameRate"].as<int>();
  info.sim.n = (info.sim.tf - info.sim.t0)/info.sim.dt;

  int num = doc["items"]["children"][worldItem]["children"].size();
  for(int i=0; i<num; i++){
    if(doc["items"]["children"][worldItem]["children"][i]["name"].as<string>()==config.body.name)
      bodyItem = i;

    if(doc["items"]["children"][worldItem]["children"][i]["name"].as<string>()=="AISTSimulator")
      aistItem = i;
  }

  for(int i=0; i<3; i++)
    try{
      ag(i) = doc["items"]["children"][worldItem]["children"][aistItem]["data"]["gravity"][i].as<double>();
    }catch(...){ag(i) = 0.;}

  for(int i=0, k=0; i<3; i++){
    limb[0].node[0].r0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootPosition"][i].as<double>();

    for(int j=0; j<3; j++, k++)
      limb[0].node[0].R0(j,i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootAttitude"][k].as<double>();

    try{
      limb[0].node[0].v0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootVelocity"][i].as<double>();
    }catch(...){limb[0].node[0].v0(i) = 0.;}
    try{
      limb[0].node[0].w0(i) = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialRootAngularVelocity"][i].as<double>();
    }catch(...){limb[0].node[0].w0(i) = 0.;}
  }

  for(int i=1, k=0; i<info.value.node; i++){
    for(int j=0; j<info.limb[i].dof; j++, k++){
      limb[i].node[j].th0 = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialJointPositions"][k].as<double>();

      try{
        limb[i].node[j].dth0 = doc["items"]["children"][worldItem]["children"][bodyItem]["data"]["initialJointVelocities"][k].as<double>();
      }catch(...){limb[i].node[j].dth0=0.;}
    }
  }
}
