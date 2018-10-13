/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"

void RLS::Config::setPath()
{
  if(debug) DEBUG;

  dir.share = dir.link + "share/";

  path_yaml.model = dir.link + "yaml/model/" + read.model;
  path_yaml.controller = dir.link + "yaml/controller/" + read.controller;
  path_yaml.output = dir.link + "yaml/output/" + read.output;
  path_yaml.rlsSimulator = dir.link + "yaml/rlsSimulator/" + read.rlsSimulator;
}
