/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

MatrixXd RLS::RlsDynamics::weight(const TreeModel::Info &info, const Vector3d &rIndex)
{
  if(debug) DEBUG;

  MatrixXd W = MatrixXd::Identity(6*info.controlNodeNum, 6*info.controlNodeNum);

  Vector3d Dr = cal_X.segment(0,3) - cal_X.segment(6,3);

  Vector3d Drk;
  double wkz;

  double wz = 0.;
  double wzTilde;

  // only foot support
  for(int i=0; i<info.controlNodeNum; i++){
    Drk = rIndex - cal_X.segment(6*i,3);
    wkz = abs(Dr.head(2).transpose()*Drk.head(2));

    wz += wkz;

    for(int j=0; j<6; j++)
      W(6*i+j,6*i+j) = wkz;
  }

  wzTilde = 1/wz;

  return W;
}
