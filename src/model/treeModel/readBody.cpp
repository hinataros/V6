/**
   @author Sho Miyahara 2017
*/

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readBody(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  vector<int> node, dof;

  YAML::Node doc = YAML::LoadFile((config.dir.body+config.body.name+".body").c_str());

  // try{
  //   if(doc["links"][0]["name"].as<string>()=="free")
  //     dof.push_back(6);
  // }catch(...){cout << "error... " << endl;};
  dof.push_back(6);
  info.dof.all += dof[0];

  node.push_back(1);
  info.value.node = node[0];
  info.value.all += node[0];

  for(unsigned i=1, nodetemp=0; i<doc["links"].size(); i++){
    try{
      if(doc["links"][i]["jointId"].as<int>()>=0)
        nodetemp++;
    }catch(...){
      dof.push_back(nodetemp);
      info.dof.joint += nodetemp;
      info.dof.all += nodetemp;

      nodetemp++;
      node.push_back(nodetemp);
      info.value.all += nodetemp;
      info.value.joint++;
      info.value.node++;

      nodetemp=0;
    };
  }

  info.limb = new Info::Limb[info.value.node];

  for(int i=0; i<info.value.node; i++){
    info.limb[i].dof = dof[i];
    info.limb[i].value = node[i];
  }

  limb = new Limb[info.value.node];
  for(int i=0; i<info.value.node; i++)
    limb[i].node = new Node[info.limb[i].value];

  initialize(config, info);

  int rigidBodyNode = 0;
  for(int i=0, node=0; i<info.value.node; i++){
    for(int j=0; j<info.limb[i].value; j++, node++){
      // joint type
      try{
        limb[i].node[j].jointType = doc["links"][node]["jointAxis"].as<string>();
      }catch(...){
        try{
          if(doc["links"][node]["jointType"].as<string>()=="free")
            limb[i].node[j].jointType = "free";
        }catch(...){
          limb[i].node[j].jointType = "fix";
        }
      }

      // joint distance
      try{
        for(int k=0; k<3; k++)
          limb[i].node[j].d(k) = doc["links"][node]["translation"][k].as<double>();
      }catch(...){limb[i].node[j].d=Vector3d::Zero();}

      // mass
      try{
        limb[i].node[j].m = doc["links"][node]["elements"][rigidBodyNode]["mass"].as<double>();
        all.m += limb[i].node[j].m;
      }catch(...){limb[i].node[j].m=0.;}

      // com
      try{
        for(int k=0; k<3; k++)
          limb[i].node[j].ri2C(k) = doc["links"][node]["elements"][rigidBodyNode]["centerOfMass"][k].as<double>();
      }catch(...){limb[i].node[j].ri2C=Vector3d::Zero();}

      // inertia matrix
      try{
        for(int k=0, m=0; k<3; k++)
          for(int l=0; l<3; l++, m++)
            limb[i].node[j].Iw_C(k,l) = doc["links"][node]["elements"][rigidBodyNode]["inertia"][m].as<double>();
      }catch(...){limb[i].node[j].Iw_C=Matrix3d::Zero();}
    }
  }

  // o(info.value.node);
  // o(node.size());

  // o(info.dof.joint);
  // o(info.dof.all);

  // o(info.value.all);
  // o(info.value.joint);
  // o(info.value.node);

  // for(int i=0; i<info.value.node; i++){
  //   o(i);
  //   o(info.limb[i].dof);
  //   o(info.limb[i].value);
  // }
  // for(int i=0; i<info.value.node; i++){
  //   for(int j=0; j<info.limb[i].value; j++){
  //     o(i);
  //     o(j);
  //     // o(limb[i].node[j].jointType);
  //     o(limb[i].node[j].d.transpose());
  //     // o(limb[i].node[j].m);
  //     // o(limb[i].node[j].ri2C.transpose());
  //     // o(limb[i].node[j].Iw_C);
  //   }
  // }
  // gc;

  // smiyahara: 場所がびみょ～
  joints(config, info);
}
