/**
   @author Sho Miyahara 2018
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

  MatrixXd Wc = MatrixXd::Zero(info.constraint.c.all, info.constraint.c.all);

  if(info.constraint.c.all==6){
    Wc = MatrixXd::Identity(6, 6);
  }
  else if(info.constraint.c.all==12){
    Vector2d r[2];
    for(int i=0, j=0; i<info.model.controlNodeNum; i++){
      if(info.constraint.c.controlNode[i]==6){
        r[j] = model->r[i].head(2);
        j++;
      }
    }

    Vector2d Dr = r[0] - r[1];

    double w1z = abs(Dr.transpose()*(rIndex - r[0]));
    double w2z = abs(Dr.transpose()*(rIndex - r[1]));

    Wc.block(6*0,6*0, 6,6) = w1z*Matrix6d::Identity();
    Wc.block(6*1,6*1, 6,6) = w2z*Matrix6d::Identity();
  }
  else if(info.constraint.c.all==18){
    Vector2d r[3];
    for(int i=0, j=0; i<info.model.controlNodeNum; i++){
      if(info.constraint.c.controlNode[i]==6){
        r[j] = model->r[i].head(2);
        j++;
      }
    }

    Vector2d Dr12 = r[1] - r[0];
    Vector2d Dr3X = rIndex - r[2];

    Matrix2d A = Matrix2d::Zero();
    A <<
      (bb_Spx*Dr12).transpose(),
      (bb_Spx*Dr3X).transpose();

    Vector2d b = Vector2d::Zero();
    b <<
      (bb_Spx*Dr12).transpose()*r[0],
      (bb_Spx*Dr3X).transpose()*r[2];

    Vector2d r12 = A.inverse()*b;

    double w1z = abs(Dr12.transpose()*(r12 - r[0]));
    double w2z = abs(Dr12.transpose()*(r12 - r[1]));

    double w3z = abs(Dr3X.transpose()*(rIndex - r[2]));
    double w12z = abs(Dr3X.transpose()*(rIndex - r12));

    Wc.block(6*0,6*0, 6,6) = ((w1z+w2z)/w2z)*w12z*Matrix6d::Identity();
    Wc.block(6*1,6*1, 6,6) = ((w1z+w2z)/w1z)*w12z*Matrix6d::Identity();
    Wc.block(6*2,6*2, 6,6) = w3z*Matrix6d::Identity();
  }

  return Wc;
}
