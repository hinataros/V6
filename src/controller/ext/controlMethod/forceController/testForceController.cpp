/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

void RLS::Ext::testForceController(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->cal_FcBarRef = pInv(io->constraintModel.mbb_CcM)*(io->cal_dLCRef + io->model->cal_GC);
}
