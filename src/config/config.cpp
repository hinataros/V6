/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "yamlConfig.hpp"

RLS::Config::Config()
{
  if(flag.debug) DEBUG;

  def = CONFIG;
  flag.debug = false; // smiyahara:ココ定義の仕方びみょー

  setLink();
}

RLS::Config::Config(int argc, char *argv[])
{
  if(flag.debug) DEBUG;

  def = CONFIG;
  flag.debug = false; // smiyahara:ココ定義の仕方びみょー

  setLink();

  readArgument(argc, argv);

  readConfig();
}
