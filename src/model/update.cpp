/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::update()
{
  if(debug) DEBUG;

  hoap2.update();
  object.update();
}
