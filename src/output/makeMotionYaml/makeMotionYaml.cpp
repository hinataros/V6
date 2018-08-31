/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeMotionYaml(const Config &config, const TreeModel::Info &info)
{
  if(debug) DEBUG;

  makeTreeModelMotionYaml(config, info);
}
