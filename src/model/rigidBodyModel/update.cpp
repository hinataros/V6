#include "config.hpp"
#include "info.hpp"
#include "rigidBodyModel.hpp"

void RLS::RigidBodyModel::update(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  // calculate this inertia and so on...
}
