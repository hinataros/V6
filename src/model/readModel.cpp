/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::readModel(Config &config)
{
  if(debug) DEBUG;

  // hoap2.readModel(config);
  hoap2.readBody(config.dir.body+config.body.name+".body");
  hoap2.readCnoid(config.dir.cnoid, config.body.name, config.clock);

  // object.readModel(config);
}
