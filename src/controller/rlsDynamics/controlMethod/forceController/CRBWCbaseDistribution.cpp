#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::CRBWCbaseDistribution()
{
  if(debug) DEBUG;

  int contact_num = constraintModel.contactLimbs.sum();

  // std::cout << "contact" << std::endl << constraintModel.contactLimbs << std::endl;

  // Eigen::MatrixXd Tx = model->bb_TC2k.transpose();
  Eigen::MatrixXd Tx = model->bb_TC2k.transpose() * model->bb_Rk;
  Eigen::VectorXd Fext = cal_dLCRef + model->cal_GC;

  Eigen::MatrixXd CGI = compute_BWC_span(Tx);

  // o(constraintModel.V_cwc);
  // o(CGI);
  vector<int> good;

  VectorXd spans_vol = pInv(CGI) * Fext;

  for (int i=0;i<spans_vol.rows();i++) {
    if (spans_vol(i) > 0.0) {
        good.push_back(i);
    } else {
      if (i < 16){
        constraintModel.V_cwc.block(0,i,6,1) = Eigen::MatrixXd::Zero(6,1);
      }
      if(16 <= i && i < 32) {
        constraintModel.V_cwc.block(6,i,6,1) = Eigen::MatrixXd::Zero(6,1);
      }
      if(32 <= i && i < 48) {
        constraintModel.V_cwc.block(12,i,6,1) = Eigen::MatrixXd::Zero(6,1);
      }
      if(48 <= i && i < 64) {
        constraintModel.V_cwc.block(18,i,6,1) = Eigen::MatrixXd::Zero(6,1);
      }
    }
  }

  // MatrixXd thinQ = MatrixXd::Zero(contact_num * 6,good.size());
  // for (int i=0;i<good.size();i++) {
  //   if (good[i] < 16){
  //     thinQ.block(0,i,6,1) = CGI.block(0,good[i],6,1);
  //   }
  //   if(16 <= good[i] && good[i] < 32) {
  //     thinQ.block(6,i,6,1) = CGI.block(6,good[i],6,1);
  //   }
  //   if(32 <= good[i] && good[i] < 48) {
  //     thinQ.block(12,i,6,1) = CGI.block(12,good[i],6,1);
  //   }
  //   if(48 <= good[i] && good[i] < 64) {
  //     thinQ.block(18,i,6,1) = CGI.block(18,good[i],6,1);
  //   }
  // }


  Eigen::MatrixXd AGI = Eigen::MatrixXd::Zero(6, contact_num * 6);
  for (int i=0, rc=0; i<4; i++) {
    if(constraintModel.contactLimbs(i)) {
      AGI.block(0,6*rc, 6,6) = (Tx).block(0, 6*i, 6, 6);
      rc++;
    }
 }



  MatrixXd V_bwc = AGI * constraintModel.V_cwc;
  // MatrixXd V_bwc = AGI * thinQ;
  // VectorXd spans_vol = VectorXd::Zero(good.size());
  spans_vol = pInv(V_bwc) * Fext;

  cal_FcBarRef = constraintModel.V_cwc * spans_vol;
  // cal_FcBarRef = thinQ * spans_vol;
  // o(cal_FcBarRef);

}
