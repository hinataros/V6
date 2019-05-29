#include "convex_solver.hpp"
#include "link_model.hpp"

#include <iomanip>
#define o(x) std::cout << #x << ":" << std::endl << std::setprecision(6) << std::scientific << x << std::endl
#define so(x) std::cout << #x << ":" << x.rows() << " × " << x.cols() << std::endl


MatrixXd Convex_solver::compute_BWC_span(MatrixXd &tb2k, MatrixXd &V_cwc, int contact_num) {

  // MatrixXd tb2k = (TB2k.transpose()*bb_Rk); // Default
  MatrixXd AGI = MatrixXd::Zero(6, contact_num * 6);
  for (int i=0; i<contact_num; i++) {
    AGI.block(0, 6*i,6 , 6) = tb2k.block(0, 6*i, 6, 6);
  }

  MatrixXd V_bwc = AGI * V_cwc.block(6*0, 0, 6*contact_num, 16*contact_num);

  return V_bwc;
}
