/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::controlMethod()
{
  if(debug) DEBUG;

  if(config.input=="velocity"||config.input=="acceleration"){
    if(!extMotionController)
      input = (this->*motionController_ptr)();
    else
      input = (ext->*ext_motionController_ptr)(this);
  }

  else if(config.input=="torque"){
    if(!extInverseDynamicsController){
      input = (this->*inverseDynamicsController_ptr)();
    }
    else
      input = (ext->*ext_inverseDynamicsController_ptr)(this);
  }

  else
    input = VectorXd::Zero(info.model.dof.joint);

  if(!extExternalWrenchController)
    (this->*externalWrenchController_ptr)();
  else
    (ext->*ext_externalWrenchController_ptr)(this);
}
