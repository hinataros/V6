
#include "config.hpp"
#include "walkingFunction.hpp"


MatrixXd RLS::WalkingFunction::makePosBoundary(int dim, double start, double finish)
{
  MatrixXd boundary = MatrixXd::Zero(dim*2, 1);
  boundary(0,0) = start;
  boundary(dim,0) = finish;
  if(dim>1){
    boundary.block(1,0, dim-1,1) = VectorXd::Zero(dim-1);
    boundary.block(dim+1,0, dim-1,1) = VectorXd::Zero(dim-1);
  }

  return boundary;
}

MatrixXd RLS::WalkingFunction::makePosBoundary(int dim, VectorXd start, VectorXd finish)
{
  if(start.rows() != finish.rows()){
    cout << "Boundary matrix size error..." << endl;
    return Matrix3d::Zero();
  }
  int rs = start.rows();

  MatrixXd boundary = MatrixXd::Zero(dim*2, rs);
  boundary.row(0) = start.transpose();
  boundary.row(dim) = finish.transpose();
  if(dim>1){
    boundary.block(1,0, dim-1,rs) = MatrixXd::Zero(dim-1, rs);
    boundary.block(dim+1,0, dim-1,rs) = MatrixXd::Zero(dim-1, rs);
  }

  return boundary;
}
