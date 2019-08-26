#include "config.hpp"
#include "walkingFunction.hpp"


MatrixXd RLS::WalkingFunction::findPolyParam(double t0, double tf, MatrixXd boundary)
{
  MatrixXd tMat = MatrixXd::Zero(boundary.rows(), boundary.rows());
  tMat <<
    maketMat(boundary.rows()/2, t0),
    maketMat(boundary.rows()/2, tf);

  return tMat.inverse()*boundary;
}

MatrixXd RLS::WalkingFunction::findPolyParam(double t0, double tf, MatrixXd start, MatrixXd finish)
{
  if(start.rows() != finish.rows() || start.cols() != finish.cols()){
    cout << "Boundary matrix size error..." << endl;
    return Matrix3d::Zero();
  }

  MatrixXd boundary = MatrixXd::Zero(start.rows()+finish.rows(), start.cols());
  boundary <<
    start,
    finish;

  return findPolyParam(t0, tf, boundary);
}


MatrixXd RLS::WalkingFunction::finddPolyParam(double t0, double tf, MatrixXd boundary)
{
  int boundSize = boundary.rows();

  MatrixXd tMat = MatrixXd::Zero(boundSize, boundSize), dtMat = MatrixXd::Zero(boundSize, boundSize);
  tMat <<
    maketMat(boundSize/2, t0),
    maketMat(boundSize/2, tf);
  dtMat <<
    MatrixXd::Zero(boundSize/2, boundSize),
    makedtMat(boundSize/2, tf);

  // d/dt (A^-1) = - A^-1 * dA * IC^-1
  MatrixXd dtMatInv = - tMat.inverse()*dtMat*tMat.inverse();

  return dtMatInv*boundary;
}
