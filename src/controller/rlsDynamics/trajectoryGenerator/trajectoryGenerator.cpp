/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::trajectoryGenerator(int controlNodeNum, double &t)
{
  if(debug) DEBUG;

  (this->*baseTranslationTrajectory_ptr)(t);
  (this->*baseOrientationTrajectory_ptr)(t);

  for(int i=0; i<controlNodeNum; i++)
    (this->*endEffectorTrajectory_ptr[i])(i, t);

  (this->*comTrajectory_ptr)(t);
  (this->*dcmTrajectory_ptr)(t);
  (this->*externalWrenchTrajectory_ptr)(t);
}
