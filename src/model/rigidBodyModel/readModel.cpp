// #include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"
#include "rigidBodyModel.hpp"

void RLS::RigidBodyModel::readModel(Config &config, Info &info)
{
  if (config.flag.debug) DEBUG;

  // YAML::Node doc = YAML::LoadFile(config.dir.model.c_str());

  initialize(config, info);

  // for(int i=0; i<3; i++)
  //   ag(i) = doc["World model"]["gravity"][i].as<double>();

  // m = doc["Body model"]["Mass"][i][j].as<double>();

  // inertia matrix
  // rR2C = doc["Body model"]["CoM"][i].as<double>();

  // limb[i].node[j].Iw_C(0,0) = doc["Body model"]["Inertia matrix"][i][j][0].as<double>();
  // limb[i].node[j].Iw_C(0,1) = doc["Body model"]["Inertia matrix"][i][j][1].as<double>();
  // limb[i].node[j].Iw_C(0,2) = doc["Body model"]["Inertia matrix"][i][j][2].as<double>();
  // limb[i].node[j].Iw_C(1,0) = doc["Body model"]["Inertia matrix"][i][j][3].as<double>();
  // limb[i].node[j].Iw_C(1,1) = doc["Body model"]["Inertia matrix"][i][j][4].as<double>();
  // limb[i].node[j].Iw_C(1,2) = doc["Body model"]["Inertia matrix"][i][j][5].as<double>();
  // limb[i].node[j].Iw_C(2,0) = doc["Body model"]["Inertia matrix"][i][j][6].as<double>();
  // limb[i].node[j].Iw_C(2,1) = doc["Body model"]["Inertia matrix"][i][j][7].as<double>();
  // limb[i].node[j].Iw_C(2,2) = doc["Body model"]["Inertia matrix"][i][j][8].as<double>();

  // initial configuration
  // for(int i=0; i<6; i++){
  //   if(i<3){
  //     rR0(i) = doc["Initial configuration"]["Initial position"][i].as<double>();
  //     vR0(i) = doc["Initial configuration"]["Initial velocity"][i].as<double>();
  //   }else{
  //     xiR0(3+i) = doc["Initial configuration"]["Initial position"][i].as<double>()*DEG2RAD;
  //     wR0(3+i) = doc["Initial configuration"]["Initial velocity"][i].as<double>();
  //   }
  // }
}
