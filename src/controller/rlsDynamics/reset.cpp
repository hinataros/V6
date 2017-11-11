#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reset(Config &config, Info &info, double &t)
{
  if(config.flag.debug) DEBUG;

  // smiyahara: 1ステップ目は初期化と同義
  rCtemp = rCf;

  rBtemp = rBf;
  xiBtemp = xiBf;

  cal_Xtemp = cal_Xf;

  readWork(config, info);

  // smiyahara: 場所がちょっとびみょ
  Bc_k = MatrixXd::Zero(6*info.value.joint, c);
  Bm_k = MatrixXd::Zero(6*info.value.joint, m);
  for(int i=0, j=0, k=0; i<6*info.value.joint; i++){
    if(Bc_kDiag(i, i)){
      Bc_k(i,j) = 1.;
      j++;
    }
    if(Bm_kDiag(i, i)){
      Bm_k(i,k) = 1.;
      k++;
    }
  }

  // motion controller
  vc_ptr = map_vc[vc_name];
  ac_ptr = map_ac[ac_name];

  info.sim.tw0 = t;
  info.sim.phase++;
}
