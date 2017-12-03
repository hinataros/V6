#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"

void RLS::Info::readInfo(Config &config)
{
  if (config.flag.debug) DEBUG;

  YAML::Node doc = YAML::LoadFile(config.dir.model.c_str());

  sim.t0 = doc["Simulation model"]["Initial time"].as<double>();
  sim.tf = doc["Simulation model"]["Finish time"].as<double>();
  sim.dt = doc["Simulation model"]["Hourly"].as<double>();

  sim.n = (sim.tf - sim.t0) / sim.dt;

  value.node = doc["Body model"]["Degree of freedom"].size();

  limb = new Info::Limb[value.node];

  for(int i=0; i<value.node; i++){
    limb[i].dof = doc["Body model"]["Degree of freedom"][i].as<int>();

    if(i==0)
      // base
      limb[i].value = 1;
    else{
      // link with EE
      value.joint++;
      limb[i].value = limb[i].dof+1;// smiyahara:ココの+1がびみょ
      dof.joint += limb[i].dof;
    }

    value.all += limb[i].value;
    dof.all += limb[i].dof;
  }
}
