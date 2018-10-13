/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::stack()
{
  if(debug) DEBUG;

  cal_VBfb <<
    vBfb,
    wBfb;
  cal_VMfb <<
    vCfb,
    wBfb;

  cal_dVBfb <<
    dvBfb,
    dwBfb;
  cal_dVMfb <<
    dvCfb,
    dwBfb;

  // cal_dVCfb <<
  //   dvCRef,
  //   IC.inverse()*(-KDlC*model.hoap2.all.lC - dIC*(cal_VM.tail(3) + IC.inverse()*HC*model.hoap2.all.dth));
}
