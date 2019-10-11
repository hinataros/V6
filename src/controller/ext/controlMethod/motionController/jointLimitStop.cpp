/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

VectorXd RLS::Ext::jointLimitStop(RlsDynamics *io, string mode)
{
  if(debug) DEBUG;

  double angleMargine = 5*DEG2RAD;

  VectorXd thDes = VectorXd::Zero(io->info.model.dof.joint);
  VectorXd dthRef = VectorXd::Zero(io->info.model.dof.joint);
  VectorXd ddthRef = VectorXd::Zero(io->info.model.dof.joint);
  
  for(int i=0; i<io->info.model.dof.joint; i++){
    if(io->model->th(i) > io->model->thMax(i)-angleMargine){
      thDes(i) = io->model->thMax(i)-angleMargine;
      dthRef(i) = io->KPth(i,i)*(thDes(i) - io->model->th(i));
      ddthRef(i) = - io->KDth(i,i)*io->model->dth(i) + io->KPth(i,i)*(thDes(i) - io->model->th(i));
    }
    
    else if(io->model->th(i) < io->model->thMin(i)+angleMargine){
      thDes(i) = io->model->thMin(i)+angleMargine;
      dthRef(i) = io->KPth(i,i)*(thDes(i) - io->model->th(i));
      ddthRef(i) = - io->KDth(i,i)*io->model->dth(i) + io->KPth(i,i)*(thDes(i) - io->model->th(i));
    }
    
    else{
      dthRef(i) = 0;
      ddthRef(i) = - io->KDth(i,i)*io->model->dth(i);
    }
    
  }
    
  if(mode == "vel")
    return dthRef;

  else if(mode == "acc")
    return ddthRef;

  else if(mode == "accInit")
    return - io->KDth*io->model->dth + io->KPth*(io->model->th0 - io->model->th);
      
  else
    return VectorXd::Zero(io->info.model.dof.joint);
}
