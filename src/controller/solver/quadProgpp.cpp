/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "quadProgpp.hpp"

VectorXd RLS::QuadProgpp::solver(MatrixXd& G, VectorXd& g0, VectorXd& x)
{
  MatrixXd Czero = MatrixXd::Zero(0, x.size());
  VectorXd czero = VectorXd::Zero(0);

  return solver(G, g0, Czero, czero, Czero, czero, x);
}

VectorXd RLS::QuadProgpp::solver(MatrixXd& G, VectorXd& g0, string c, MatrixXd& C, VectorXd& c0, VectorXd& x)
{
  MatrixXd Czero = MatrixXd::Zero(0, x.size());
  VectorXd czero = VectorXd::Zero(0);

  if(c=="e"){
    return solver(G, g0, C, c0, Czero, czero, x);
  }
  if(c=="i"){
    return solver(G, g0, Czero, czero, C, c0, x);
  }
}

VectorXd RLS::QuadProgpp::solver(MatrixXd& G, VectorXd& g0, MatrixXd& CE, VectorXd& ce0, MatrixXd& CI, VectorXd& ci0, VectorXd& x)
{
#ifdef QUADPROGPP
  quadprogpp::solve_quadprog(G, g0, CE.transpose(), -ce0, CI.transpose(), -ci0, x);
#endif

  return x;
}
