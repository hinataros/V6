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
}

RLS::Config::Config(int argc, char *argv[])
{
  if(debug) DEBUG;

  initialize();
  setLink();

  readArgument(argc, argv);

  readConfig();
}
