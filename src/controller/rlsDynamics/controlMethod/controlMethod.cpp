/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::controlMethod(const string controlInput, const TreeModel::Info &info)
{
  if(debug) DEBUG;

  if(controlInput=="velocity"||controlInput=="acceleration")
    input = (this->*motionController_ptr)(info);

  else if(controlInput=="torque")
    input = (this->*inverseDynamicsController_ptr)(info);

  else
    cout << "no such control input..." << endl;
}
