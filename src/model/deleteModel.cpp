/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"

void RLS::Model::deleteModel(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  // smiyahara: 分岐希望
  hoap2.deleteModel(config, info);
}
