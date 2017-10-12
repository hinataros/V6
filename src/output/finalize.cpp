#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::finalize(Config &config)
{
  if (config.flag.debug) DEBUG;

  vector<TreeModelList>().swap(data.tm);
  vector<RlsDynamicsList>().swap(data.dc);
}
