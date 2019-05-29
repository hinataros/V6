/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::localInitialize()
{
  if(debug) DEBUG;

  // high gain control
  thDes = model->th0;

  // amiyata for foot print
  contactFlag = new bool[info.model.controlNodeNum];
  for(int i=0; i<4; i++){
    contactFlag[i] = false;
  }
  footPrintList.clear();
  footPrintList.shrink_to_fit();

// #ifdef CONVEXSOLVER
//   // CWC
//   vector<string> contact_links;
//   contact_links.push_back("Foot_R");
//   contact_links.push_back("Foot_L");
//   // contact_links.push_back("Hand_R");
//   // contact_links.push_back("Hand_L");
//
//   // convex_solver.init(TB2k.transpose()*bb_Rk);  // (1)
//   ConvexSolver::compute_CWC_span(contact_links);
// #endif
}
