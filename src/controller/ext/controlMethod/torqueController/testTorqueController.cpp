/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

void RLS::Ext::testTorqueController(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->tau = io->model->gth - io->cal_Jc.transpose()*io->cal_FcBarRef;
}
