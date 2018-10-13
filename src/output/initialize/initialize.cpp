/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::initialize(const string &dir_link, const string &path_yaml_output, Info &info, const int &controllerNum, const WorldModel &worldModel)
{
  if(debug) DEBUG;

  setDefaultValue();

  readOutput(path_yaml_output);
  setDir(dir_link);

  setModel(worldModel, info, controllerNum);

  initializeData();

  setMap();
}
