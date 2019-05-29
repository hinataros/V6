#include "convex_solver.hpp"
#include "link_model.hpp"

MatrixXd Convex_solver::compute_FC_span(std::string _link_name) {

  MatrixXd M_face_y = MatrixXd::Zero(16, 12);

  const double pi = 3.141592653589793;

  // double mu = 0.5;
  double mu = 0.2;
  double qq = sqrt(1*1+mu*mu);

  MatrixXd S0;

  S0 = MatrixXd::Zero(12, 16);

  for (int i=0; i<4; i++){
    // // 外接円
    // S0.block(3*i, 4*i, 3, 4) <<
    //   mu,  mu, -mu, -mu,
    //   mu, -mu, -mu,  mu,
    //    1,   1,   1,   1;

    // // 内接円
    // S0.block(3*i, 4*i, 3, 4) <<
    //   mu,   0, -mu,   0,
    //    0,  mu,   0, -mu,
    //    1,   1,   1,   1;

    // // 外接円(正規化)
    // S0.block(3*i, 4*i, 3, 4) <<
    //   mu/qq,  mu/qq, -mu/qq, -mu/qq,
    //   mu/qq, -mu/qq, -mu/qq,  mu/qq,
    //    1/qq,   1/qq,   1/qq,   1/qq;

    // 内接円(正規化)
    S0.block(3*i, 4*i, 3, 4) <<
      mu/qq,      0, -mu/qq,      0,
          0,  mu/qq,      0, -mu/qq,
       1/qq,   1/qq,   1/qq,   1/qq;

  }


  // viewMatrix("S0 --", S0);

  //    1, 0,  0, 1, 0,  0, 1,  0,  0,  1,  0, 0,
  //    0, 1,  0, 0, 1,  0, 0,  1,  0,  0,  1, 0,
  //    0, 0,  1, 0, 0,  1, 0,  0,  1,  0,  0, 1,
  //    0, 0,  Y, 0, 0, -Y, 0,  0, -Y,  0,  0, Y,
  //    0, 0, -X, 0, 0, -X, 0,  0,  X,  0,  0, X,
  //   -Y, X,  0, Y, X,  0, Y, -X,  0, -Y, -X, 0;
  LinkModel link = LinkModel(_link_name);
  MatrixXd CM  = MatrixXd::Zero(6, 12);
  for (int i=0; i< 4; i++) {
    CM.block(0,3*i,3,3) = MatrixXd::Identity(3,3);
    CM.block(3,3*i,3,3) = -crossmat(link.length_x[i], link.length_y[i], 0.0);
  }

  MatrixXd V_fc = CM * S0;
  return V_fc;
}
