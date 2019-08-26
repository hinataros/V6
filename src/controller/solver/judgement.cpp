#include <iostream>

#include "config.hpp"
#include "common.hpp"

#include "cfsqp.hpp"

void RLS::CFSQP::Ejudgement(MatrixXd CE, VectorXd ce0, VectorXd xRet)
{
  for(int i=0; i<CE.rows(); i++) {
    if(fabs(CE.row(i) * xRet - ce0(i)) > 1.e-10)
      cout << "Equal constraint is not satisfied: " << i << endl << "Difference of CE(" << i << ") * x and ce(" << i <<") :" << endl << CE.row(i) * xRet - ce0(i) << endl;
  }
}

void RLS::CFSQP::Ijudgement(MatrixXd CI, VectorXd ci0, VectorXd xRet)
{
  for(int i=0; i<CI.rows(); i++) {
    if ((CI.row(i) * xRet - ci0(i)) < -1.e-10) // 10^-16 オーダーでははみ出る
      cout << "Inequal constraint is not satisfied: " << i << endl << "Difference of CI(" << i << ") * x and ci(" << i <<") :" << endl << CI.row(i) * xRet - ci0(i) << endl;
  }
}
