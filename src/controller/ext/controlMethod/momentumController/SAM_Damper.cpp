/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::SAM_Damper(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->dlCRef = - io->KDlC*(io->model->IC*io->model->wB + io->model->HC*io->model->dth);

}
