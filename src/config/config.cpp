/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"

bool debug = false;

RLS::Config::Config()
{
  if(debug) DEBUG;

  initialize();
  setLink();
  readInitYaml();
}

RLS::Config::Config(int argc, char *argv[])
{
  if(debug) DEBUG;

  initialize();
  setLink();
  readInitYaml();

  readArgument(argc, argv);

  readConfig();
}
