#include "convex_solver.hpp"
#include "link_model.hpp"

MatrixXd Convex_solver::compute_CWC_span(std::vector<std::string> _contact_links) {

  // =====
  // V cwc の計算
  // =====

  int contact_num = _contact_links.size();
  int spans_col = 0;

  std::vector<MatrixXd> spans;

  for (int i=0; i<contact_num; i++) {
    spans.push_back( compute_FC_span(_contact_links[i]) );
  }

  for (int i=0;i<spans.size();i++) {
    spans_col += spans[i].cols();
  }

  MatrixXd V = MatrixXd::Zero(contact_num * 6, spans_col);

  // view_matrix("span", spans[0]);

  for (int i=0; i<spans.size(); i++) {
    V.block(6*i, spans[i].cols()*i,6 , spans[i].cols()) = spans[i];
  }

  // =====
  // BWC 用にサイズ合わせ
  // ====

  MatrixXd V_cwc = MatrixXd::Zero(24, 16*contact_num);
  int col = 0;
  for (int i=0; i<contact_num; i++) {
    if (_contact_links[i] == "Foot_R") {
      V_cwc.block(6*0, 0,6 , 16*contact_num) = V.block(col*6, 0, 6, 16*contact_num);
      col += 1;
    }
    if (_contact_links[i] == "Foot_L") {
      V_cwc.block(6*1, 0, 6 , 16*contact_num) = V.block(col*6, 0, 6, 16*contact_num);
      col += 1;
    }
    if (_contact_links[i] == "Hand_R") {
      V_cwc.block(6*2,0,6 , 16*contact_num) = V.block(col*6,0, 6, 16*contact_num);
      col += 1;
    }
    if (_contact_links[i] == "Hand_L") {
      V_cwc.block(6*3,0,6 , 16*contact_num) = V.block(col*6,0, 6, 16*contact_num);
      col += 1;
    }
  }

  return V_cwc;
}
