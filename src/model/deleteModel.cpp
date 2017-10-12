#include "config.hpp"
#include "info.hpp"
#include "model.hpp"

void RLS::Model::deleteModel(Config &config, Info &info)
{
  if (config.flag.debug) DEBUG;

  // smiyahara: 分岐希望
  TreeModel::deleteModel(config, info);
}
