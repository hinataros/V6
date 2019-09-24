/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"


MatrixXd RLS::ConstraintModel::compute_FC_span(string _link_name) {

  double mu = 0.5;
  // double mu = 0.2;
  double qq = sqrt(1*1+mu*mu);

  MatrixXd S0 = MatrixXd::Zero(12, 16);

  for (int i=0; i<4; i++){
    // 内接円(正規化)
    S0.block(3*i, 4*i, 3, 4) <<
      mu/qq,      0, -mu/qq,      0,
          0,  mu/qq,      0, -mu/qq,
       1/qq,   1/qq,   1/qq,   1/qq;

  }

  //    1, 0,  0, 1, 0,  0, 1,  0,  0,  1,  0, 0,
  //    0, 1,  0, 0, 1,  0, 0,  1,  0,  0,  1, 0,
  //    0, 0,  1, 0, 0,  1, 0,  0,  1,  0,  0, 1,
  //    0, 0,  Y, 0, 0, -Y, 0,  0, -Y,  0,  0, Y,
  //    0, 0, -X, 0, 0, -X, 0,  0,  X,  0,  0, X,
  //   -Y, X,  0, Y, X,  0, Y, -X,  0, -Y, -X, 0;
  // LinkModel link = LinkModel(_link_name);
  MatrixXd CM  = MatrixXd::Zero(6, 12);
  Vector3d Lengths = Vector3d::Zero();
  for (int i=0; i<4; i++) {
    if(model->model->link[info.model->controlNode[info.model->controlNodeID[_link_name]].num].eeSize.rows() == 0){
      cout << "constraintModel::compute_FC_span: eeSize desn't have any data!" << endl;
      break;
    }

    Lengths <<
      model->model->link[info.model->controlNode[info.model->controlNodeID[_link_name]].num].eeSize(i, 0),
      model->model->link[info.model->controlNode[info.model->controlNodeID[_link_name]].num].eeSize(i, 1),
      0.0;

    CM.block(0,3*i,3,3) = MatrixXd::Identity(3,3);
    CM.block(3,3*i,3,3) = -cross(Lengths);
  }

  MatrixXd V_fc = CM * S0;
  return V_fc;
}


MatrixXd RLS::ConstraintModel::compute_CWC_span() {

  MatrixXd V = MatrixXd::Zero(6*(int)contactLimbs.sum(), 16*(int)contactLimbs.sum());
  // o(contactLimbs);

  for (int i=0,rc=0; i<info.model->controlNodeNum; i++) {
    if(contactLimbs(i)) {
      V.block(6*rc,16*rc, 6,16) = compute_FC_span(info.model->controlNode[i].name);
      rc++;
      // o(V);
    }
  }

  return V;
}
