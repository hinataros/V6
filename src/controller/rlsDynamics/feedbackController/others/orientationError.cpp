/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

Vector3d RLS::FeedbackController::orientationError(const Matrix3d &RDes, const Matrix3d &R)
{
  if(debug) DEBUG;

  Vector3d eo = Vector3d::Zero();

  // new
  // ****************
  Matrix3d dR = RDes*R.transpose();

  Vector3d t = Vector3d::Zero();
  t <<
    dR(2,1) - dR(1,2),
    dR(0,2) - dR(2,0),
    dR(1,0) - dR(0,1);

  double dphi = atan2(t.norm(), dR(0,0)+dR(1,1)+dR(2,2)-1);

  if(t.norm())
    eo = abs(dphi)*(t/t.norm());
  // ****************

  // // old
  // // ****************
  // for(int i=0; i<3; i++)
  //   eo += cross(R.col(i))*RDes.col(i);

  // eo *= 0.5;
  // // ****************

  return eo;
}
