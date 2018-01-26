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

  YAML::Node doc = YAML::LoadFile(config.dir.body.c_str());

  info.value.node = doc["Body model"]["Degree of freedom"].size();

  info.limb = new Info::Limb[info.value.node];

  for(int i=0; i<info.value.node; i++){
    info.limb[i].dof = doc["Body model"]["Degree of freedom"][i].as<int>();

    if(i==0)
      // base
      info.limb[i].value = 1;
    else{
      // link with EE
      info.value.joint++;
      info.limb[i].value = info.limb[i].dof+1;// smiyahara:ココの+1がびみょ
      info.dof.joint += info.limb[i].dof;
    }

    info.value.all += info.limb[i].value;
    info.dof.all += info.limb[i].dof;
  }

  limb = new Limb[info.value.node];
  for(int i=0; i<info.value.node; i++)
    limb[i].node = new Node[info.limb[i].value];

  initialize(config, info);

  for(int i=0; i<info.value.node; i++){
    for(int j=0; j<info.limb[i].value; j++){
      // joint type
      limb[i].node[j].jointType = doc["Body model"]["Joint type"][i][j].as<string>();

      // joint distance
      for(unsigned k=0; k<doc["Body model"]["Joint distance"][i][j].size(); k++)
        limb[i].node[j].d(k) = doc["Body model"]["Joint distance"][i][j][k].as<double>();

      // mass
      limb[i].node[j].m = doc["Body model"]["Mass"][i][j].as<double>();
      all.m += limb[i].node[j].m;

      // com
      for(unsigned k=0; k<doc["Body model"]["CoM"][i][j].size(); k++)
        limb[i].node[j].ri2C(k) = doc["Body model"]["CoM"][i][j][k].as<double>();

      // inertia matrix
      limb[i].node[j].Iw_C(0,0) = doc["Body model"]["Inertia matrix"][i][j][0].as<double>();
      limb[i].node[j].Iw_C(0,1) = doc["Body model"]["Inertia matrix"][i][j][1].as<double>();
      limb[i].node[j].Iw_C(0,2) = doc["Body model"]["Inertia matrix"][i][j][2].as<double>();
      limb[i].node[j].Iw_C(1,0) = doc["Body model"]["Inertia matrix"][i][j][3].as<double>();
      limb[i].node[j].Iw_C(1,1) = doc["Body model"]["Inertia matrix"][i][j][4].as<double>();
      limb[i].node[j].Iw_C(1,2) = doc["Body model"]["Inertia matrix"][i][j][5].as<double>();
      limb[i].node[j].Iw_C(2,0) = doc["Body model"]["Inertia matrix"][i][j][6].as<double>();
      limb[i].node[j].Iw_C(2,1) = doc["Body model"]["Inertia matrix"][i][j][7].as<double>();
      limb[i].node[j].Iw_C(2,2) = doc["Body model"]["Inertia matrix"][i][j][8].as<double>();
    }
  }

  // smiyahara: 場所がびみょ～
  joints(config, info);
}
