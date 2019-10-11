/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::SAM_RNS(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->dlCRef =  io->model->IC*io->fb.dwBfb + io->model->dIC*io->model->wB - io->KDlC*io->model->HC*io->model->dth;

}
