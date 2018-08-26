/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

YAML::Node RLS::RlsDynamics::checkNode(YAML::Node &doc, string node, int phase, string name)
{
  return doc[node][phase][name];
}
YAML::Node RLS::RlsDynamics::checkNode(YAML::Node &doc, string node, int phase, string name1, string name2)
{
  return doc[node][phase][name1][name2];
}
YAML::Node RLS::RlsDynamics::checkNode(YAML::Node &doc, string node, int num, int phase, string name)
{
  return doc[node][num][phase][name];
}
YAML::Node RLS::RlsDynamics::checkNode(YAML::Node &doc, string node, int num, int phase, string name1, string name2)
{
  return doc[node][num][phase][name1][name2];
}

