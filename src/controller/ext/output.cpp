/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

void RLS::Ext::output(RlsDynamics *io)
{
  if(debug) DEBUG;

  outputList.jointLimitGradient = VectorXd::Zero(io->info.model.dof.joint);
  for(int i=0; i<io->info.model.dof.joint; i++)
    outputList.jointLimitGradient(i) = (io->model->th(i) - io->model->thMid(i))/(io->model->thMax(i) - io->model->thMid(i));

  for(int i=0; i<3; i++){
    outputList.WCRB(i) = W(i+3,i+3);
    outputList.dWCRB(i) = dW(i+3,i+3);
  }

  outputList.wC = io->model->wB + Jw*io->model->dth;
  outputList.Dw = Jw*io->model->dth;
  outputList.wB = io->model->wB;

  outputList.DwLower = Jw.block(0,0,3,12)*io->model->dth.head(12);
  outputList.DwUpper = Jw.block(0,12,3,io->info.model.dof.joint-12)*io->model->dth.head(io->info.model.dof.joint-12);

  outputList.dwCRef = dwCRef;
  outputList.dDwRef = dDwRef;
  outputList.dwBRef = io->fb.dwBfb;

  outputList.dlCRefRoot = io->dlCRef;
  outputList.dlCRefMotion = io->model->IC*io->fb.dwBfb + io->model->dIC*io->model->wB + io->model->HC*io->ddthRef + io->model->dHC*io->model->dth;
  // outputList.dlCRefMotion = io->model->IC*io->fb.dwBfb + io->model->HC*io->ddthRef;
  outputList.dlCRefError = outputList.dlCRefRoot - outputList.dlCRefMotion;
  outputList.dlCComponent = io->model->dHC*io->model->dth;
  // outputList.dlCComponent = io->model->IC*io->fb.dwBfb + io->model->HC*io->ddthRef;

  VectorXd dwB = VectorXd::Zero(3);
  VectorXd ddth = VectorXd::Zero(io->info.model.dof.joint);
  static VectorXd wBPre = VectorXd::Zero(3);
  static VectorXd dthPre = VectorXd::Zero(io->info.model.dof.joint);
  
  dwB = (io->model->wB - wBPre)/io->worldModel->dt;
  ddth = (io->model->dth - dthPre)/io->worldModel->dt;

  wBPre = io->model->wB;
  dthPre = io->model->dth;

  outputList.dlC = io->model->IC*io->fb.dwBfb + io->model->dIC*io->model->wB + io->model->HC*io->ddthRef + io->model->dHC*io->model->dth;
  outputList.dlCRB = io->model->IC*io->fb.dwBfb + io->model->dIC*io->model->wB;
  outputList.dlCAM = io->model->HC*io->ddthRef + io->model->dHC*io->model->dth;

}
