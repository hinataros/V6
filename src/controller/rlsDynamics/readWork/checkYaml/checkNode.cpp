/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::checkNode(YAML::Node &doc, string node, int seq, string name)
{
  doc[node][seq][name].as<string>();
}

void RLS::RlsDynamics::checkNode(YAML::Node &doc, string node, int seq, string name, int i)
{
  doc[node][seq][name][i].as<string>();
}

void RLS::RlsDynamics::checkNode(YAML::Node &doc, string node, int seq, string name, int i, int j)
{
  doc[node][seq][name][i][j].as<string>();
}
