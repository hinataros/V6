/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setEEPosition(const int num, Vector3d *r0, Matrix3d *xi0)
{
  if(debug) DEBUG;

  rxw0 = VectorXd::Zero(6*num);

  for(int i=0; i<num; i++){
    rxw0.segment(i*6, 6) <<
      r0[i],
      R2xi(xi0[i]);
  }
}
