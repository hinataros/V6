#include "convex_solver.hpp"

void Convex_solver::view_matrix(std::string txt, MatrixXd mat) {

  std::cout << txt << std::endl;
  std::cout << mat.rows() << "x" << mat.cols() << std::endl;;
  for (int i=0; i<mat.rows(); i++){
    for (int j=0; j<mat.cols(); j++) {
      std::cout << mat(i, j) << " ";
    }
    std::cout << std::endl;
  }

}
