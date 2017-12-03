#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readModel(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  YAML::Node doc = YAML::LoadFile(config.dir.model.c_str());

  limb = new Limb[info.value.node];
  for(int i=0; i<info.value.node; i++)
    limb[i].node = new Node[info.limb[i].value];

  initialize(config, info);

  for(int i=0; i<3; i++)
    ag(i) = doc["World model"]["gravity"][i].as<double>();

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

    // initial configuration
    if(i==0)
      for(int j=0; j<info.limb[i].dof; j++){
  	if(j<3){
  	  limb[0].node[0].r0(j) = doc["Initial configuration"]["Initial position"][i][j].as<double>();
  	  limb[0].node[0].v0(j) = doc["Initial configuration"]["Initial velocity"][i][j].as<double>();
  	}else{
  	  limb[0].node[0].xi0(j-3) = doc["Initial configuration"]["Initial position"][i][j].as<double>()*DEG2RAD;
  	  limb[0].node[0].w0(j-3) = doc["Initial configuration"]["Initial velocity"][i][j].as<double>();
  	}
      }
    else{
      for(int j=0; j<info.limb[i].dof; j++){
  	limb[i].node[j].th0 = doc["Initial configuration"]["Initial position"][i][j].as<double>() * DEG2RAD;
  	limb[i].node[j].dth0 = doc["Initial configuration"]["Initial velocity"][i][j].as<double>();
      }
    }
  }

  // smiyahara: 場所がびみょ～
  joints(config, info);
}
