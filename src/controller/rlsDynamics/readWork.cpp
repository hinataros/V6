#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readWork(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string path = config.link + "yaml/work/" + config.controller.name + "/" + config.controller.work +".yaml";

  YAML::Node doc = YAML::LoadFile(path.c_str());
  info.sim.twf = doc["Control"][info.sim.phase]["twf"].as<double>();

  // smiyahara: このforは下のやつとあわせてもいい
  int cur=0, temp;
  c=0;m=0;
  for(int i=0; i<info.value.joint; i++){
    temp=0;
    for(int j=0; j<6; j++){
      Bc_kDiag(cur+j,cur+j) = doc["Control"][info.sim.phase]["Bc"][i][j].as<int>();
      Bm_kDiag(cur+j,cur+j) = doc["Control"][info.sim.phase]["Bm"][i][j].as<int>();

      if(Bc_kDiag(cur+j,cur+j))
	c++;
      if(Bm_kDiag(cur+j,cur+j))
	m++;

      temp++;
    }

    cur += temp;
  }

  for(int i=0; i<3; i++){
    rCf(i) = doc["Control"][info.sim.phase]["rCf"][i].as<double>();
    rBf(i) = doc["Control"][info.sim.phase]["rBf"][i].as<double>();
    xiBf(i) = doc["Control"][info.sim.phase]["xiBf"][i].as<double>()*DEG2RAD;
  }

  cur=0;
  for(int i=0; i<info.value.joint; i++){
    temp=0;
    for(int j=0; j<6; j++){
      cal_Xf(cur+j) = doc["Control"][info.sim.phase]["cal_Xf"][i][j].as<double>();
      if(j>2)
	cal_Xf(cur+j) *= DEG2RAD;

      temp++;
    }

    cur += temp;
  }

  // gain
  kpC = doc["Control"][info.sim.phase]["kpC"].as<double>();
  kdC = doc["Control"][info.sim.phase]["kdC"].as<double>();

  kpvB = doc["Control"][info.sim.phase]["kpvB"].as<double>();
  kdvB = doc["Control"][info.sim.phase]["kdvB"].as<double>();

  kpwB = doc["Control"][info.sim.phase]["kpwB"].as<double>();
  kdwB = doc["Control"][info.sim.phase]["kdwB"].as<double>();
}
