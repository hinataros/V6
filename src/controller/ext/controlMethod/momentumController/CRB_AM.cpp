/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::CRB_AM(RlsDynamics *io)
{
  if(debug) DEBUG;

  // RNSAccelerationDistribution(io);

  io->dlCRef =  io->model->IC*io->fb.dwBfb + io->model->dIC*io->model->wB;

}
