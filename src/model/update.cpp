#include "config.hpp"
#include "info.hpp"
#include "model.hpp"

void RLS::Model::update(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  hoap2.update(config, info);
  object.update(config, info);
}
