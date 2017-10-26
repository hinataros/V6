#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::readWork(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string path = config.link + "yaml/work/"
    + config.controller.name + "/" + config.controller.work + ".yaml";
  YAML::Node doc = YAML::LoadFile(path.c_str());

  info.sim.twf = doc["Control"][info.sim.phase]["twf"].as<double>();

  try{
    doc["Control"][info.sim.phase]["Bc"][0][0].as<int>();

    c=0;
    for(int i=0, temp=0; i<info.value.joint; temp+=6, i++)
      for(int j=0; j<6; j++){
	Bc_kDiag(temp+j,temp+j) = doc["Control"][info.sim.phase]["Bc"][i][j].as<int>();

	if(Bc_kDiag(temp+j,temp+j))
	  c++;
      }
  }
  catch(...){}

  try{
    doc["Control"][info.sim.phase]["Bm"][0][0].as<int>();

    m=0;
    for(int i=0, temp=0; i<info.value.joint; temp+=6, i++)
      for(int j=0; j<6; j++){
  	Bm_kDiag(temp+j,temp+j) = doc["Control"][info.sim.phase]["Bm"][i][j].as<int>();

  	if(Bm_kDiag(temp+j,temp+j))
  	  m++;
      }
  }
  catch(...){}

  try{
    for(int i=0; i<3; i++)
      rCf(i) = doc["Control"][info.sim.phase]["rCf"][i].as<double>();
  }
  catch(...){}
  try{
    for(int i=0; i<3; i++)
      rBf(i) = doc["Control"][info.sim.phase]["rBf"][i].as<double>();
  }
  catch(...){}
  try{
    for(int i=0; i<3; i++)
      xiBf(i) = doc["Control"][info.sim.phase]["xiBf"][i].as<double>()*DEG2RAD;
  }
  catch(...){}

  try{
    doc["Control"][info.sim.phase]["cal_Xf"][0][0].as<double>();

    for(int i=0, temp=0; i<info.value.joint; temp+=6, i++)
      for(int j=0; j<6; j++){
  	cal_Xf(temp+j) = doc["Control"][info.sim.phase]["cal_Xf"][i][j].as<double>();

  	if(j>2)
  	  cal_Xf(temp+j) *= DEG2RAD;
      }
  }
  catch(...){}

  // gain
  try{
    kpC = doc["Control"][info.sim.phase]["kpC"].as<double>();
  }
  catch(...){}
  try{
    kpvB = doc["Control"][info.sim.phase]["kpvB"].as<double>();
  }
  catch(...){}
  try{
    kpwB = doc["Control"][info.sim.phase]["kpwB"].as<double>();
  }
  catch(...){}
}
