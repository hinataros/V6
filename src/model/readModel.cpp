#include "config.hpp"
#include "info.hpp"
#include "model.hpp"

void RLS::Model::readModel(Config &config, Info &info)
{
  if (config.flag.debug) DEBUG;

  TreeModel::readModel(config, info);
  RigidBodyModel::readModel(config, info);
}
