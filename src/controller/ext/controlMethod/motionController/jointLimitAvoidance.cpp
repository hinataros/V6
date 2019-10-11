/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

VectorXd RLS::Ext::jointLimitAvoidance(RlsDynamics *io, string mode)
{
  if(debug) DEBUG;

  VectorXd gradh = VectorXd::Zero(io->info.model.dof.joint);
  double Beta = 0.3;

  for(int i=0; i<io->info.model.dof.joint; i++){
    gradh(i) = (io->model->th(i) - io->model->thMid(i))/pow(io->model->thMid(i) - io->model->thMax(i),2);
  }

  VectorXd dthDes = -Beta*gradh;

  if(mode == "vel")
    return dthDes;

  else if(mode == "acc")
    return io->KDth*(dthDes - io->model->dth);

  else
    return VectorXd::Zero(io->info.model.dof.joint);
}
