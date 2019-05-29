#include "convex_solver.hpp"

MatrixXd Convex_solver::crossmat(double x, double y, double z) {
  MatrixXd r = MatrixXd::Zero(3, 3);
  r <<
    0, -z,  y,
    z,  0, -x,
   -y,  x,  0;
  return r;
}
