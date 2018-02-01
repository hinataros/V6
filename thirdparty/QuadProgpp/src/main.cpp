/*
  File main.cc

  This file contains just an example on how to set-up the matrices for using with
  the solve_quadprog() function.

  The test problem is the following:

  Given:
  G =  4 -2   g0^T = [6 0]
  -2  4

  Solve:
  min f(x) = 1/2 x G x + g0 x
  s.t.
  x_1 + x_2 = 3
  x_1 >= 0
  x_2 >= 0
  x_1 + x_2 >= 2

  The solution is x^T = [1 2] and f(x) = 12

  Author: Luca Di Gaspero
  DIEGM - University of Udine, Italy
  l.digaspero@uniud.it
  http://www.diegm.uniud.it/digaspero/

  Copyright 2006-2009 Luca Di Gaspero

  This software may be modified and distributed under the terms
  of the MIT license.  See the LICENSE file for details.

  @rewrite Sho Miyahara 2017
*/

#include <iostream>
#include <sstream>
#include <string>
#include "QuadProg++.hpp"

int main(int argc, char *const argv[])
{
  MatrixXd G, CE, CI;
  VectorXd g0, ce0, ci0, x;
	int n, m, p;
	double sum = 0.0;
	char ch;

  n = 2;

  G = MatrixXd::Zero(n, n);
  G <<
    4., -2.,
    -2., 4.;

  g0 = VectorXd::Zero(n);
  g0 <<
    6.,
    0.;

  m = 1;
  CE = MatrixXd::Zero(n, m);
  CE <<
    1.,
    1.;

  ce0 = VectorXd::Zero(m);
  ce0 <<
    -3.;

	p = 3;

  CI = MatrixXd::Zero(n, p);
  CI <<
    1., 0., 1.,
    0., 1., 1.;

  ci0 = VectorXd::Zero(p);
  ci0 <<
    0.,
    0.,
    -2.;

  x = VectorXd::Zero(n);

  std::cout << "f: " << quadprogpp::solve_quadprog(G, g0, CE, ce0, CI, ci0, x) << std::endl;
	std::cout << "x: " << x << std::endl;
  /*  for (int i = 0; i < n; i++)
      std::cout << x[i] << ' ';
      std::cout << std::endl;	 */

	/* FOR DOUBLE CHECKING COST since in the solve_quadprog routine the matrix G is modified */

  G <<
    4., -2.,
    -2., 4.;

  std::cout << "Double checking cost: ";
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			sum += x(i)*G(i,j)*x(j);
	sum *= 0.5;

	for(int i=0; i<n; i++)
		sum += g0(i)*x(i);
	std::cout << sum << std::endl;
}
