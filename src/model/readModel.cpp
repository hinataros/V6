/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::readModel(Config &config)
{
  if(debug) DEBUG;

  hoap2.readModel(config.dir.model);
  hoap2.setDir(config.dir.share);
  hoap2.readBody();
  hoap2.readCnoid(config.clock);

  // object.readModel(config);
}
