/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

VectorXd RLS::Ext::testMotionController(RlsDynamics *io)
{
  if(debug) DEBUG;

  return io->ddqMoptRef;
}
