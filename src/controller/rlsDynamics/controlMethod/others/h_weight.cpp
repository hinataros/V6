/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

MatrixXd RLS::RlsDynamics::h_weight(const Vector2d &rIndex, const Vector2d &r1, const Vector2d &r2)
{
  if(debug) DEBUG;

  Vector2d Dr = r1 - r2;

  double w1z = abs(Dr.transpose()*(rIndex - r1));
  double w2z = abs(Dr.transpose()*(rIndex - r2));

  Matrix6d W1 = w1z*Matrix6d::Identity();
  Matrix6d W2 = w2z*Matrix6d::Identity();

  MatrixXd W = MatrixXd::Zero(12,12);
  W.block(0,0,6,6) = W1;
  W.block(6,6,6,6) = W2;

  return W;
}

MatrixXd RLS::RlsDynamics::h_weight(const Vector2d &rIndex)
{
  if(debug) DEBUG;

  VectorXd cal_Xc = Bc.transpose()*cal_X;
  MatrixXd Wc = MatrixXd::Zero(cal_Xc.size(), cal_Xc.size());

  if(cal_Xc.size()==12){
    Vector2d r1 = cal_Xc.segment(0,2);
    Vector2d r2 = cal_Xc.segment(6,2);
    Vector2d Dr = r1 - r2;

    double w1z = abs(Dr.transpose()*(rIndex - r1));
    double w2z = abs(Dr.transpose()*(rIndex - r2));

    Wc.block(6*0,6*0, 6,6) = w1z*Matrix6d::Identity();
    Wc.block(6*1,6*1, 6,6) = w2z*Matrix6d::Identity();
  }
  else if(cal_Xc.size()==18){
    Vector2d r1 = cal_Xc.segment(0,2);
    Vector2d r2 = cal_Xc.segment(6,2);
    Vector2d r3 = cal_Xc.segment(12,2);

    Vector2d Dr12 = r2 - r1;
    Vector2d Dr3X = rIndex - r3;

    Matrix2d A = Matrix2d::Zero();
    A <<
      (bb_Spx*Dr12).transpose(),
      (bb_Spx*Dr3X).transpose();

    Vector2d b = Vector2d::Zero();
    b <<
      (bb_Spx*Dr12).transpose()*r1,
      (bb_Spx*Dr3X).transpose()*r3;

    Vector2d r12 = A.inverse()*b;

    double w1z = abs(Dr12.transpose()*(r12 - r1));
    double w2z = abs(Dr12.transpose()*(r12 - r2));

    double w3z = abs(Dr3X.transpose()*(rIndex - r3));
    double w12z = abs(Dr3X.transpose()*(rIndex - r12));

    Wc.block(6*0,6*0, 6,6) = ((w1z+w2z)/w2z)*w12z*Matrix6d::Identity();
    Wc.block(6*1,6*1, 6,6) = ((w1z+w2z)/w1z)*w12z*Matrix6d::Identity();
    Wc.block(6*2,6*2, 6,6) = w3z*Matrix6d::Identity();
  }

  return Wc;
}
