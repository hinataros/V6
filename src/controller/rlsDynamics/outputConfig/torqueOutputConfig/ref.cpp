/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputRefConfig(const TreeModel::Info &info)
{
  if(debug) DEBUG;

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

  dc_list.rvrpRef = rX - drXRef/wX;

  dc_list.dpRef = dpRef;
  dc_list.dlCRef = dlCRef;

  // dc_list.dlBRef = dlBRef;

  dc_list.fRef = dc_list.nRef
    = VectorXd::Zero(3*info.controlNodeNum);
  for(int i=0; i<info.controlNodeNum; i++){
    dc_list.fRef.segment(3*i, 3) = (Bc_k*cal_FcBarRef).segment(6*i, 3);
    dc_list.nRef.segment(3*i, 3) = (Bc_k*cal_FcBarRef).segment(6*i+3, 3);
  }

  dc_list.cal_FextRef = cal_FextRef;

  dc_list.tau = tau;
}
