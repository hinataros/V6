/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputErrConfig()
{
  if(debug) DEBUG;

  outputList.erB = fb.erB;
  outputList.evB = fb.evB;
  outputList.eoB = fb.eoB;
  outputList.ewB = fb.ewB;

  outputList.eX = fb.eX;

  outputList.erC = fb.erC;
  outputList.evC = fb.evC;

  outputList.er = outputList.ev
    = outputList.eo = outputList.ew
    = outputList.ef = outputList.en
    = VectorXd::Zero(3*info.model.controlNodeNum);

  for(int i=0; i<info.model.controlNodeNum; i++){
    outputList.er.segment(3*i, 3) = fb.cal_Ep.segment(6*i, 3);
    outputList.eo.segment(3*i, 3) = antiDiag(3,1.,1.,1.)*fb.cal_Ep.segment(6*i+3, 3);

    outputList.ev.segment(3*i, 3) = fb.cal_Ev.segment(6*i, 3);
    outputList.ew.segment(3*i, 3) = fb.cal_Ev.segment(6*i+3, 3);

    outputList.ef.segment(3*i, 3) = (constraintModel.Bc_k*cal_FcBarRef - model->cal_F).segment(6*i, 3);
    outputList.en.segment(3*i, 3) = (constraintModel.Bc_k*cal_FcBarRef - model->cal_F).segment(6*i+3, 3);
  }
}
