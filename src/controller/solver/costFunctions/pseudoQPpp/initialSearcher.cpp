#include "config.hpp"
#include "common.hpp"

#include "costFunctionQPpp.hpp"


void RLS::costFunctionQPpp::initialSearcher(double *xRet)
{
  VectorXd xIn;

  if(preX.rows() == 0) { //最初
    // if(CEo.rows() != 0)
    //   xIn = pInv(CEo) * ceo;
    // else
    //   xIn = pInv(CIo) * cio;
    MatrixXd condM;
    MatrixXd condV;
    int ms = CEo.cols();
    // if(CEo.cols() < CIo.cols())
    //   ms = CIo.cols();
    // condM = MatrixXd::Zero(CEo.rows()+CIo.rows(), ms);
    condM = MatrixXd::Zero(CEo.rows(), ms);
    // condV = VectorXd::Zero(CEo.rows()+CIo.rows());
    condV = VectorXd::Zero(CEo.rows());

    condM <<
      CEo;
      // CIo;
    condV <<
      ceo;
      // cio;
    xIn = pInv(condM) * condV;

  }else
    xIn = preX;

  for(int i(0); i<CEo.cols(); i++)
    xRet[i] = xIn(i);
}
