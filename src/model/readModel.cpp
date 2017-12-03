#include "config.hpp"
#include "info.hpp"
#include "model.hpp"

void RLS::Model::readModel(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  hoap2.readModel(config, info);
  object.readModel(config, info);
}
