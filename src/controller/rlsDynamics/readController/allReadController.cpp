/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

void RLS::RlsDynamics::allReadController()
{
  if(debug) DEBUG;

  if(!extractor.readFlag){
    des.readController();
    fb.readController();
    readController(extractor.controllers.controlMethod);
    
    extractor.readFlag = true;
  } else {
    des.readController();
    fb.readController();
    readController();
  }

  // amiyata controllerだけ独立
  readParameter();

  ext->readController(this);
}
