/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"

void RLS::Model::readModel(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  // hoap2.readModel(config, info);
  hoap2.readBody(config, info);
  hoap2.readCnoid(config, info);

  object.readModel(config, info);
}
