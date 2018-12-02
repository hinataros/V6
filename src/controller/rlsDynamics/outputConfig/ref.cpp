/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputRefConfig()
{
  if(debug) DEBUG;

  outputList.dvBfb = fb.dvBfb;

  outputList.dvCfb = fb.dvCfb;
  outputList.dwBfb = fb.dwBfb;
  outputList.ddthRef = ddthRef;

  // outputList.dvBoptRef = fb.ddqBoptRef.head(3);
  // outputList.dwBoptRef = fb.ddqBoptRef.segment(3,3);
  // outputList.ddthoptRef = fb.ddqBoptRef.tail(info.dof.joint);

  outputList.dvCoptRef = ddqMoptRef.head(3);
  outputList.dwBoptRef = ddqMoptRef.segment(3,3);
  outputList.ddthoptRef = ddqMoptRef.tail(info.model.dof.joint);

  outputList.rvrpRef = model->rX - fb.drXfb/model->wX;

  outputList.dpRef = dpRef;
  outputList.dlCRef = dlCRef;

  outputList.dlBRef = dlBRef;

  outputList.fRef = outputList.nRef
    = VectorXd::Zero(3*info.model.controlNodeNum);
  for(int i=0; i<info.model.controlNodeNum; i++){
    outputList.fRef.segment(3*i, 3) = (constraintModel.Bc_k*cal_FcBarRef).segment(6*i, 3);
    outputList.nRef.segment(3*i, 3) = (constraintModel.Bc_k*cal_FcBarRef).segment(6*i+3, 3);
  }

  outputList.cal_Fextfb = fb.cal_Fextfb;

  outputList.tau = tau;
}
