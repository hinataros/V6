/**
   @author Sho Miyahara 2017
   @editor Akinori Miyata 2019
*/

#include "config.hpp"

#include "interpolation.hpp"


void RLS::Interpolation::unitQuaternionFix(Quaternion4d &qD, Quaternion4d &dqD, Quaternion4d &ddqD)
{
  VectorXd q_NU, dq_NU, ddq_NU;
  VectorXd q, dq, ddq;
  q = dq = ddq = q_NU = dq_NU = ddq_NU = VectorXd::Zero(4);

  q_NU << qD.w, qD.v;
  dq_NU << dqD.w, dqD.v;
  ddq_NU << ddqD.w, ddqD.v;

  q = q_NU / sqrt(q_NU.transpose() * q_NU);
  dq = (MatrixXd::Identity(4,4) - q*q.transpose()) * dq_NU / sqrt(q_NU.transpose() * q_NU);

  double A = dq.transpose() * dq;
  ddq = - A * q + (MatrixXd::Identity(4,4) - q * q.transpose()) * ddq_NU / sqrt(q_NU.transpose() * q_NU);

  qD.w = q(0);
  qD.v = q.tail(3);
  dqD.w = dq(0);
  dqD.v = dq.tail(3);
  ddqD.w = ddq(0);
  ddqD.v = ddq.tail(3);
}
