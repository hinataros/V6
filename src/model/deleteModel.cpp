/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::deleteModel()
{
  if(debug) DEBUG;

  // smiyahara: 分岐希望
  hoap2.deleteModel();
}
