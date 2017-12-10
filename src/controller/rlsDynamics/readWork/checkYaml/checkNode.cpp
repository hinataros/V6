#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::checkNode(Config &config, Info &info, YAML::Node &doc, string name)
{
  if(config.flag.debug) DEBUG;

  doc["Work"][info.sim.phase][name].as<string>();
}

void RLS::RlsDynamics::checkNode(Config &config, Info &info, YAML::Node &doc, string name, int i)
{
  if(config.flag.debug) DEBUG;

  doc["Work"][info.sim.phase][name][i].as<string>();
}

void RLS::RlsDynamics::checkNode(Config &config, Info &info, YAML::Node &doc, string name, int node, int i)
{
  if(config.flag.debug) DEBUG;

  doc["Work"][info.sim.phase][name][node][i].as<string>();
}
