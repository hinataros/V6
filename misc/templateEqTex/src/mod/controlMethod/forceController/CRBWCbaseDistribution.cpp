#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::CRBWCbaseDistribution()
{
  if(debug) DEBUG;

  int contact_num = constraintModel.contactLimbs.sum();

  Eigen::MatrixXd Tx = model->bb_TC2k.transpose();
  Eigen::VectorXd Fext = cal_dLCRef + model->cal_GC;

  Eigen::MatrixXd CGI = compute_BWC_span(Tx);
// こっからわからん
  vector<int> bad;
  for (int i=0;i<contact_num * 16;i++) {
    if (CGI.col(i).transpose()*(Fext) >= 0) {
      bad.push_back(i);
    }
  }

  MatrixXd thinQ = MatrixXd::Zero(contact_num * 6,bad.size());
  for (int i=0;i<bad.size();i++) {
    if (bad[i] < 16){
      thinQ.block(0,i,6,1) = constraintModel.V_cwc.block(0,bad[i],6,1);
    }
    if(16 <= bad[i] && bad[i] < 32) {
      thinQ.block(6,i,6,1) = constraintModel.V_cwc.block(6,bad[i],6,1);
    }
    if(32 <= bad[i] && bad[i] < 48) {
      thinQ.block(12,i,6,1) = constraintModel.V_cwc.block(12,bad[i],6,1);
    }
    if(48 <= bad[i] && bad[i] < 64) {
      thinQ.block(18,i,6,1) = constraintModel.V_cwc.block(18,bad[i],6,1);
    }
  }

  Eigen::MatrixXd AGI = Eigen::MatrixXd::Zero(6, contact_num * 6);
  for (int i=0; i<contact_num; i++) {
    AGI.block(0, 6*i,6 , 6) = (Tx).block(0, 6*i, 6, 6);
  }

  MatrixXd V_bwc = AGI * thinQ;
  VectorXd spans_vol = VectorXd::Zero(bad.size()); //(cal_dLBRef + model->cal_GB);
  spans_vol = pInv(V_bwc) * Fext;

  cal_FcBarRef = thinQ * spans_vol;

}
