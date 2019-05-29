#ifndef CONVEX_HPP
#define CONVEX_HPP

#include <iostream>
#include <string>
#include <vector>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

class Convex_solver
{
public:
  // double mu;
  // MatrixXd XGI;
  // MatrixXd H_fc;
  // MatrixXd V_fc;
  // MatrixXd H_cwc;
  // MatrixXd V_cwc;
  // MatrixXd H_bwc;
  // MatrixXd V_bwc;
  // int contact_num;

  MatrixXd crossmat(double, double, double);
  void view_matrix(std::string, MatrixXd);

  MatrixXd compute_FC_span(std::string);
  MatrixXd compute_CWC_span(std::vector<std::string>);
  MatrixXd compute_BWC_span(MatrixXd&, MatrixXd&, int);

};

#endif
