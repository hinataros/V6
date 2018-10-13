/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"

void RLS::Config::initialize()
{
  if(debug) DEBUG;

  _init_config = "default";

  shm.flag = false;

  read.model = "default";
  read.controller = "default";

  path_yaml.config = "default";
  path_yaml.model = "default";
  path_yaml.controller = "default";
}
