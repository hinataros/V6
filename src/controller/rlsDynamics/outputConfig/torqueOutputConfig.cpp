/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputConfig(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // desired values
  dc_list.rBDes = rBDes;
  dc_list.vBDes = vBDes;
  dc_list.dvBDes = dvBDes;

  dc_list.xiBDes = antiDiag(3,1.,1.,1.)*xiBDes;
  dc_list.wBDes = wBDes;
  dc_list.dwBDes = dwBDes;

  dc_list.rCDes = rCDes;
  dc_list.vCDes = vCDes;
  dc_list.dvCDes = dvCDes;

  dc_list.rXDes = rXDes;
  dc_list.drXDes = drXDes;

  dc_list.rvrpDes = rX - drXDes/wX;

  dc_list.rDes = dc_list.vDes = dc_list.dvDes
    = dc_list.xiDes = dc_list.wDes = dc_list.dwDes
    = VectorXd::Zero(3*info.value.joint);

  for(int i=0; i<info.value.joint; i++){
    dc_list.rDes.segment(3*i, 3) = cal_XDes.segment(6*i, 3);
    dc_list.xiDes.segment(3*i, 3) = antiDiag(3,1.,1.,1.)*cal_XDes.segment(6*i+3, 3);

    dc_list.vDes.segment(3*i, 3) = cal_VDes.segment(6*i, 3);
    dc_list.wDes.segment(3*i, 3) = cal_VDes.segment(6*i+3, 3);

    dc_list.dvDes.segment(3*i, 3) = cal_dVDes.segment(6*i, 3);
    dc_list.dwDes.segment(3*i, 3) = cal_dVDes.segment(6*i+3, 3);
  }

  // error values
  dc_list.erB = erB;
  dc_list.evB = evB;
  dc_list.eoB = eoB;
  dc_list.ewB = ewB;

  dc_list.eX = eX;

  dc_list.erC = erC;
  dc_list.evC = evC;

  dc_list.er = dc_list.ev
    = dc_list.eo = dc_list.ew
    = dc_list.ef = dc_list.en
    = VectorXd::Zero(3*info.value.joint);
  for(int i=0; i<info.value.joint; i++){
    dc_list.er.segment(3*i, 3) = cal_Ep.segment(6*i, 3);
    dc_list.eo.segment(3*i, 3) = antiDiag(3,1.,1.,1.)*cal_Ep.segment(6*i+3, 3);

    dc_list.ev.segment(3*i, 3) = cal_Ev.segment(6*i, 3);
    dc_list.ew.segment(3*i, 3) = cal_Ev.segment(6*i+3, 3);

    dc_list.ef.segment(3*i, 3) = (Bc_k*cal_FcBarRef - cal_F).segment(6*i, 3);
    dc_list.en.segment(3*i, 3) = (Bc_k*cal_FcBarRef - cal_F).segment(6*i+3, 3);
  }

  // dc_list.dvBRef = dvBRef;
  // dc_list.dwBRef = dwBRef;
  // dc_list.ddthRef = ddthRef;

  dc_list.dvCRef = dvCRef;
  dc_list.dwBRef = dwBRef;
  dc_list.ddthRef = ddthRef;

  // dc_list.dvBoptRef = ddqBoptRef.head(3);
  // dc_list.dwBoptRef = ddqBoptRef.segment(3,3);
  // dc_list.ddthoptRef = ddqBoptRef.tail(info.dof.joint);

  dc_list.dvCoptRef = ddqMoptRef.head(3);
  dc_list.dwBoptRef = ddqMoptRef.segment(3,3);
  dc_list.ddthoptRef = ddqMoptRef.tail(info.dof.joint);

  dc_list.dpRef = dpRef;
  dc_list.dlCRef = dlCRef;

  // dc_list.dlBRef = dlBRef;

  dc_list.fRef = dc_list.nRef
    = VectorXd::Zero(3*info.value.joint);
  for(int i=0; i<info.value.joint; i++){
    dc_list.fRef.segment(3*i, 3) = (Bc_k*cal_FcBarRef).segment(6*i, 3);
    dc_list.nRef.segment(3*i, 3) = (Bc_k*cal_FcBarRef).segment(6*i+3, 3);
  }

  dc_list.cal_FextRef = cal_FextRef;

  dc_list.tau = tau;

  dc_list.pCRB = model.hoap2.all.m*cal_VM.head(3);
  dc_list.lCRB = IC*cal_VM.tail(3);

  dc_list.pCth = Vector3d::Zero();
  dc_list.lCth = HC*model.hoap2.all.dth;

  dc_list.p = model.hoap2.all.m*cal_VM.head(3);
  dc_list.lC = IC*cal_VM.tail(3) + HC*model.hoap2.all.dth;

  // index
  // cop
  dc_list.rp = rp;

  // replace x <==> y
  dc_list.rpk = VectorXd::Zero(2*info.value.joint);
  for(int i=0; i<info.value.joint; i++)
    dc_list.rpk.segment(2*i, 2) = antiDiag(2,1.,1.)*rpk.segment(2*i, 2);

  dc_list.rpkx = dc_list.rpky
    = VectorXd::Zero(1*info.value.joint);
  for(int i=0; i<info.value.joint; i++){
    dc_list.rpkx(i) = rpk(2*i);
    dc_list.rpky(i) = rpk(2*i+1);
  }

  // cmp
  dc_list.rcmp = rcmp;

  // dcm
  dc_list.rX = rX;
}
