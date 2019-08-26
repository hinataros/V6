#include "config.hpp"
#include "common.hpp"

#include "costFunctionQPpp.hpp"


RLS::costFunctionQPpp::costFunctionQPpp(MatrixXd G, VectorXd g, MatrixXd CE, VectorXd ce, MatrixXd CI, VectorXd ci)
{
  Go = G;
  go = g;
  CEo = CE;
  ceo = ce;
  CIo = CI;
  cio = ci;
}

RLS::costFunctionQPpp::costFunctionQPpp()
{
  
}

RLS::costFunctionQPpp::~costFunctionQPpp()
{

}


void RLS::costFunctionQPpp::configuration(MatrixXd G, VectorXd g, MatrixXd CE, VectorXd ce, MatrixXd CI, VectorXd ci)
{
  Go = G;
  go = g;
  CEo = CE;
  ceo = ce;
  CIo = CI;
  cio = ci;
}
