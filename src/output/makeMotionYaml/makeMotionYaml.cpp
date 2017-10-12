#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeMotionYaml(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  makeTreeModelMotionYaml(config, info);
}
