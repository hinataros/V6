/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

void RLS::Ext::testMomentumController(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->dpRef = io->model->M*io->fb.dvCfb;
  io->dlCRef = io->model->IC*io->fb.dwBfb + io->model->IC*io->model->wB;

  io->cal_dLCRef <<
    io->dpRef,
    io->dlCRef;
}
