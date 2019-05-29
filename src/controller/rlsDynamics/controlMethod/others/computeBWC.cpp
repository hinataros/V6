/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"


MatrixXd RLS::RlsDynamics::compute_BWC_span(MatrixXd &tb2k) {

  // MatrixXd tb2k = (TB2k.transpose()*bb_Rk); // Default
  MatrixXd AGI = MatrixXd::Zero(6, (int)constraintModel.contactLimbs.sum()*6);
  for (int i=0, rc=0; i<(int)constraintModel.contactLimbs.sum(); i++) {
    if(constraintModel.contactLimbs(i)) {
      AGI.block(0,6*rc, 6,6) = tb2k.block(0,6*i, 6,6);
      rc++;
    }
  }

  MatrixXd V_bwc = AGI * constraintModel.V_cwc;

  return V_bwc;
}
