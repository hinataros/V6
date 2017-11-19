#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeModelDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  makeTreeModelDat(config, info);
}