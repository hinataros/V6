/**
   @author Sho Miyahara 2017
*/

#ifdef CONVEXSOLVER
#include "convex_solver.hpp"
#endif

namespace RLS{
  class ConvexSolver{
  private:
  public:
#ifdef CONVEXSOLVER
    Convex_solver convex_solver;
#endif

    // MatrixXd XGI;
    // MatrixXd H_fc;
    // MatrixXd V_fc;
    // MatrixXd H_cwc;
    MatrixXd V_cwc;
    // MatrixXd H_bwc;
    MatrixXd V_bwc;

    MatrixXd compute_FC_span(string);
    MatrixXd compute_CWC_span(vector<string>);
    MatrixXd compute_BWC_span(MatrixXd, int);
  };
}
