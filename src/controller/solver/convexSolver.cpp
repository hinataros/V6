/**
   @author Sho Miyahara 2017

   1/2 x^T G x + g^T x
   CE x = ce
   CI x >= ci
*/

#include "config.hpp"
#include "convexSolver.hpp"


MatrixXd RLS::ConvexSolver::compute_FC_span(string _link_name)
{
#ifdef CONVEXSOLVER
  V_bwc = convex_solver.compute_FC_span(_link_name);
  return V_bwc;
#endif

  cout << "not linked solver..." << endl;
  return MatrixXd::Zero(0,0);
}

MatrixXd RLS::ConvexSolver::compute_CWC_span(vector<string> _contact_links)
{
#ifdef CONVEXSOLVER
  V_cwc = convex_solver.compute_CWC_span(_contact_links);
  return V_cwc;
#endif

  cout << "not linked solver..." << endl;
  return MatrixXd::Zero(0,0);
}

MatrixXd RLS::ConvexSolver::compute_BWC_span(MatrixXd tb2k, int contact_num)
{
#ifdef CONVEXSOLVER
  V_bwc = convex_solver.compute_BWC_span(tb2k, V_cwc, contact_num);
  return V_bwc;
#endif

  cout << "not linked solver..." << endl;
  return MatrixXd::Zero(0,0);
}
