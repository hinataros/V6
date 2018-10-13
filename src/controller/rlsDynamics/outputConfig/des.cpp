/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputDesConfig()
{
  if(debug) DEBUG;

  outputList.rBDes = des.rBDes;
  outputList.vBDes = des.vBDes;
  outputList.dvBDes = des.dvBDes;

  outputList.xiBDes = antiDiag(3,1.,1.,1.)*des.xiBDes;
  outputList.wBDes = des.wBDes;
  outputList.dwBDes = des.dwBDes;

  outputList.rCDes = des.rCDes;
  outputList.vCDes = des.vCDes;
  outputList.dvCDes = des.dvCDes;

  outputList.rXDes = des.rXDes;
  outputList.drXDes = des.drXDes;

  outputList.rvrpDes =
    model->rX - des.drXDes/model->wX;

  outputList.rDes = outputList.vDes = outputList.dvDes
    = outputList.xiDes = outputList.wDes = outputList.dwDes
    = VectorXd::Zero(3*info.model.controlNodeNum);

  for(int i=0; i<info.model.controlNodeNum; i++){
    outputList.rDes.segment(3*i, 3) = des.cal_XDes.segment(6*i, 3);
    outputList.xiDes.segment(3*i, 3) = antiDiag(3,1.,1.,1.)*des.cal_XDes.segment(6*i+3, 3);

    outputList.vDes.segment(3*i, 3) = des.cal_VDes.segment(6*i, 3);
    outputList.wDes.segment(3*i, 3) = des.cal_VDes.segment(6*i+3, 3);

    outputList.dvDes.segment(3*i, 3) = des.cal_dVDes.segment(6*i, 3);
    outputList.dwDes.segment(3*i, 3) = des.cal_dVDes.segment(6*i+3, 3);
  }
}
