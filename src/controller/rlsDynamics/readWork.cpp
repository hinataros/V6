#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readWork(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string path = config.dir.link + "yaml/work/" + config.controller.name + "/" + config.controller.work +".yaml";
  YAML::Node doc = YAML::LoadFile(path.c_str());

  info.sim.twf = doc["Work"][info.sim.phase]["twf"].as<double>();

  try{
    mc_name = doc["Work"][info.sim.phase]["Motion controller"].as<string>();
  }
  catch(...){}
  try{
    tc_name = doc["Work"][info.sim.phase]["Torque controller"].as<string>();
  }
  catch(...){}

  try{
    doc["Work"][info.sim.phase]["Bc"][0][0].as<int>();

    c=0;
    for(int i=0, temp=0; i<info.value.joint; temp+=6, i++)
      for(int j=0; j<6; j++){
	Bc_kDiag(temp+j,temp+j) = doc["Work"][info.sim.phase]["Bc"][i][j].as<int>();

	if(Bc_kDiag(temp+j,temp+j))
	  c++;
      }
  }
  catch(...){}

  try{
    doc["Work"][info.sim.phase]["Bm"][0][0].as<int>();

    m=0;
    for(int i=0, temp=0; i<info.value.joint; temp+=6, i++)
      for(int j=0; j<6; j++){
  	Bm_kDiag(temp+j,temp+j) = doc["Work"][info.sim.phase]["Bm"][i][j].as<int>();

  	if(Bm_kDiag(temp+j,temp+j))
  	  m++;
      }
  }
  catch(...){}

  try{
    for(int i=0; i<3; i++)
      rCf(i) = doc["Work"][info.sim.phase]["rCf"][i].as<double>();
  }
  catch(...){}
  try{
    for(int i=0; i<3; i++)
      rBf(i) = doc["Work"][info.sim.phase]["rBf"][i].as<double>();
  }
  catch(...){}
  try{
    for(int i=0; i<3; i++)
      xiBf(i) = doc["Work"][info.sim.phase]["xiBf"][i].as<double>()*DEG2RAD;
  }
  catch(...){}

  try{
    doc["Work"][info.sim.phase]["cal_Xf"][0][0].as<double>();

    for(int i=0, temp=0; i<info.value.joint; temp+=6, i++)
      for(int j=0; j<6; j++){
  	cal_Xf(temp+j) = doc["Work"][info.sim.phase]["cal_Xf"][i][j].as<double>();

  	if(j>2)
  	  cal_Xf(temp+j) *= DEG2RAD;
      }
  }
  catch(...){}

  // gain
  try{
    kpC = doc["Work"][info.sim.phase]["kpC"].as<double>();
  }
  catch(...){}
  try{
    kdC = doc["Work"][info.sim.phase]["kdC"].as<double>();
  }
  catch(...){}

  try{
    kpvB = doc["Work"][info.sim.phase]["kpvB"].as<double>();
  }
  catch(...){}
  try{
    kdvB = doc["Work"][info.sim.phase]["kdvB"].as<double>();
  }
  catch(...){}

  try{
    kpwB = doc["Work"][info.sim.phase]["kpwB"].as<double>();
  }
  catch(...){}
  try{
    kdwB = doc["Work"][info.sim.phase]["kdwB"].as<double>();
  }
  catch(...){}
  try{
    kpv = doc["Work"][info.sim.phase]["kpv"].as<double>();
  }
  catch(...){}
  try{
    kdv = doc["Work"][info.sim.phase]["kdv"].as<double>();
  }
  catch(...){}

  try{
    kthD = doc["Work"][info.sim.phase]["kthD"].as<double>();
  }
  catch(...){}

  // high gain control
  try{
    kpHG = doc["Work"][info.sim.phase]["kpHG"].as<double>();
  }
  catch(...){}
  try{
    kdHG = doc["Work"][info.sim.phase]["kdHG"].as<double>();
  }
  catch(...){}
}
