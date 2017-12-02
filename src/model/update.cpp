#include "config.hpp"
#include "info.hpp"
#include "model.hpp"

void RLS::Model::update(Config &config, Info &info)
{
  if (config.flag.debug) DEBUG;

  TreeModel::update(config, info);
  RigidBodyModel::update(config, info);
}
