/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

Matrix3d RLS::Common::R(string axis, double th)
{
  Matrix3d R = Matrix3d::Zero();

  if(axis=="E"||axis=="no axis")
    R = Matrix3d::Identity();

  else{
    double s = math("s",1, th);
    double c = math("c",1, th);

    if(axis=="x" || axis=="X")
      R <<
        1, 0, 0,
        0, c,-s,
        0, s, c;

    else if(axis=="y" || axis=="Y")
      R <<
        c, 0, s,
        0, 1, 0,
        -s,0, c;

    else if(axis=="z" || axis=="Z")
      R <<
        c,-s, 0,
        s, c, 0,
        0, 0, 1;

    else
      cout << "axis error..." << endl;
  }

  return R;
}
