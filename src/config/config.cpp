/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "yamlConfig.hpp"

bool debug =false;

RLS::Config::Config()
{
  if(debug) DEBUG;

  def = CONFIG;
  // debug = false; // smiyahara:ココ定義の仕方びみょー

  setLink();
}

RLS::Config::Config(int argc, char *argv[])
{
  if(debug) DEBUG;

  def = CONFIG;
  // debug = false; // smiyahara:ココ定義の仕方びみょー

  setLink();

  readArgument(argc, argv);

  readConfig();
}
