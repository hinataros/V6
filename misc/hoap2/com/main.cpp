/**
   @author Sho Miyahara 2017
*/

#include <string>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <cmath>

#define MM 1e-3

#define BODY_LINK1 0.09e+3
#define BODY_LINK2 0.034e+3
#define HEAD_LINK1 0.081e+3
#define HEAD_LINK2 0.008e+3
#define WAIST_LINK1 0.055e+3
#define WAIST_LINK2 0.034e+3

#define ARM_LINK1 0.0995e+3
#define ARM_LINK2 0.1010e+3
#define ARM_LINK3 0.1460e+3

#define LEG_LINK1 0.0390e+3
#define LEG_LINK2 0.1000e+3
#define LEG_LINK3 0.1000e+3
#define LEG_LINK4 0.0370e+3

using namespace std;
using namespace Eigen;

struct CoM{
  Vector3d leg1;
  Vector3d leg2;
  Vector3d leg3;
  Vector3d leg4;
  Vector3d leg5;
  Vector3d leg6;

  Vector3d arm1;
  Vector3d arm2;
  Vector3d arm3;
  Vector3d arm4;
} r,l;

Matrix3d R(string, double);

Vector3d com(string);
Matrix3d RNode(string);
Vector3d transNode(string, string);
Vector3d posNode(string);
Vector3d localCoM(string);

int main()
{
  r.leg1 = com("RLEG1")*MM;
  cout << "R leg 1 CoM postion:" << endl;
  cout << r.leg1 << endl;

  r.leg2 = com("RLEG2")*MM;
  cout << "R leg 2 CoM postion:" << endl;
  cout << r.leg2 << endl;

  r.leg3 = com("RLEG3")*MM;
  cout << "R leg 3 CoM postion:" << endl;
  cout << r.leg3 << endl;

  r.leg4 = com("RLEG4")*MM;
  cout << "R leg 4 CoM postion:" << endl;
  cout << r.leg4 << endl;

  r.leg5 = com("RLEG5")*MM;
  cout << "R leg 5 CoM postion:" << endl;
  cout << r.leg5 << endl;

  r.leg6 = com("RLEG6")*MM;
  cout << "R leg 6 CoM postion:" << endl;
  cout << r.leg6 << endl;

  l.leg1 = com("LLEG1")*MM;
  cout << "L leg 1 CoM postion:" << endl;
  cout << l.leg1 << endl;

  l.leg2 = com("LLEG2")*MM;
  cout << "L leg 2 CoM postion:" << endl;
  cout << l.leg2 << endl;

  l.leg3 = com("LLEG3")*MM;
  cout << "L leg 3 CoM postion:" << endl;
  cout << l.leg3 << endl;

  l.leg4 = com("LLEG4")*MM;
  cout << "L leg 4 CoM postion:" << endl;
  cout << l.leg4 << endl;

  l.leg5 = com("LLEG5")*MM;
  cout << "L leg 5 CoM postion:" << endl;
  cout << l.leg5 << endl;

  l.leg6 = com("LLEG6")*MM;
  cout << "L leg 6 CoM postion:" << endl;
  cout << l.leg6 << endl;

  r.arm1 = com("RARM1")*MM;
  cout << "R arm 1 CoM postion:" << endl;
  cout << r.arm1 << endl;

  r.arm2 = com("RARM2")*MM;
  cout << "R arm 2 CoM postion:" << endl;
  cout << r.arm2 << endl;

  r.arm3 = (transNode("RARM3","RARM4") + com("RARM3"))*MM;
  cout << "R arm 3 CoM postion:" << endl;
  cout << r.arm3 << endl;

  r.arm4 = com("RARM4")*MM;
  cout << "R arm 4 CoM postion:" << endl;
  cout << r.arm4 << endl;


  l.arm1 = com("LARM1")*MM;
  cout << "L arm 1 CoM postion:" << endl;
  cout << l.arm1 << endl;

  l.arm2 = com("LARM2")*MM;
  cout << "L arm 2 CoM postion:" << endl;
  cout << l.arm2 << endl;

  l.arm3 = (transNode("LARM3","LARM4") + com("LARM3"))*MM;
  cout << "L arm 3 CoM postion:" << endl;
  cout << l.arm3 << endl;

  l.arm4 = com("LARM4")*MM;
  cout << "L arm 4 CoM postion:" << endl;
  cout << l.arm4 << endl;

  return 0;
}

Vector3d com(string node)
{
  return RNode(node).transpose()*localCoM(node);
}

Matrix3d RNode(string node)
{
  Matrix3d E = Matrix3d::Identity();

  if(node=="BODY1")
    return E;
  if(node=="BODY2")
    return R("x", -M_PI/2);
  if(node=="HEAD1")
    return E;
  if(node=="HEAD2")
    return R("x", M_PI/2);

  if(node=="RLEG1"||node=="LLEG1")
    return R("z", -M_PI/2);
  if(node=="RLEG2"||node=="LLEG2")
    return R("y", M_PI/2)*R("z", M_PI);
  if(node=="RLEG3"||node=="LLEG3")
    return R("y", M_PI/2)*R("z", M_PI/2);
  if(node=="RLEG4"||node=="LLEG4")
    return R("y", M_PI/2)*R("z", M_PI/2);
  if(node=="RLEG5"||node=="LLEG5")
    return R("y", M_PI/2)*R("z", M_PI/2);
  if(node=="RLEG6"||node=="LLEG6")
    return R("y", M_PI/2)*R("z", M_PI);

  if(node=="RARM1"||node=="LARM1")
    return R("x", M_PI/2);
  if(node=="RARM2"||node=="LARM2")
    return R("z", -M_PI/2);
  if(node=="RARM3"||node=="LARM3")
    return R("y", M_PI/2)*R("z", M_PI);
  if(node=="RARM4"||node=="LARM4")
    return R("y", M_PI/2)*R("z", M_PI/2);

  return Matrix3d::Zero();
}

Vector3d transNode(string nodeP, string nodeC)
{
  Vector3d p = posNode(nodeP);
  Vector3d c = posNode(nodeC);

  return c - p;
}

Vector3d posNode(string node)
{
  Vector3d r;
  if(node=="BODY1")
    r <<
      0.,
      0.,
      WAIST_LINK1;
  if(node=="BODY2")
    r <<
      WAIST_LINK2,
      0.,
      WAIST_LINK1;
  if(node=="HEAD1")
    r <<
      0.,
      0.,
      BODY_LINK1 + WAIST_LINK1;
  if(node=="HEAD2")
    r <<
      HEAD_LINK2,
      0.,
      HEAD_LINK1 + BODY_LINK1 + WAIST_LINK1;

  if(node=="RLEG1")
    r <<
      0.,
      -LEG_LINK1,
      0.;
  if(node=="RLEG2")
    r <<
      0.,
      -LEG_LINK1,
      0.;
  if(node=="RLEG3")
    r <<
      0.,
      -LEG_LINK1,
      0.;
  if(node=="RLEG4")
    r <<
      0.,
      -LEG_LINK1,
      -LEG_LINK2;
  if(node=="RLEG5")
    r <<
      0.,
      -LEG_LINK1,
      -LEG_LINK2-LEG_LINK3;
  if(node=="RLEG6")
    r <<
      0.,
      -LEG_LINK1,
      -LEG_LINK2-LEG_LINK3;
  if(node=="LLEG1")
    r <<
      0.,
      LEG_LINK1,
      0.;
  if(node=="LLEG2")
    r <<
      0.,
      LEG_LINK1,
      0.;
  if(node=="LLEG3")
    r <<
      0.,
      LEG_LINK1,
      0.;
  if(node=="LLEG4")
    r <<
      0.,
      LEG_LINK1,
      -LEG_LINK2;
  if(node=="LLEG5")
    r <<
      0.,
      LEG_LINK1,
      -LEG_LINK2-LEG_LINK3;
  if(node=="LLEG6")
    r <<
      0.,
      LEG_LINK1,
      -LEG_LINK2-LEG_LINK3;
  if(node=="RARM1")
    r <<
      0.,
      -ARM_LINK1,
      WAIST_LINK1+BODY_LINK1;
  if(node=="RARM2")
    r <<
      0.,
      -ARM_LINK1,
      WAIST_LINK1+BODY_LINK1;
  if(node=="RARM3")
    r <<
      0.,
      -ARM_LINK1,
      WAIST_LINK1+BODY_LINK1;
  if(node=="RARM4")
    r <<
      ARM_LINK2,
      -ARM_LINK1,
      WAIST_LINK1+BODY_LINK1;
  if(node=="LARM1")
    r <<
      0.,
      ARM_LINK1,
      WAIST_LINK1+BODY_LINK1;
  if(node=="LARM2")
    r <<
      0.,
      ARM_LINK1,
      WAIST_LINK1+BODY_LINK1;
  if(node=="LARM3")
    r <<
      0.,
      ARM_LINK1,
      WAIST_LINK1+BODY_LINK1;
  if(node=="LARM4")
    r <<
      ARM_LINK2,
      ARM_LINK1,
      WAIST_LINK1+BODY_LINK1;

  return r;
}

Vector3d localCoM(string node)
{
  Vector3d rC;

  if(node=="BODY1")
    rC <<
      -4.86368e+1,
      1.19112e-2,
      8.60519e+1;
  if(node=="BODY2")
    rC <<
      -2.57370e+1,
      5.56017e+0,
      -3.62639e-1;
  if(node=="HEAD1")
    rC <<
      2.0678e+0,
      5.98154e-1,
      5.68043e+1;
  if(node=="HEAD2")
    rC <<
      5.29518e-1,
      -3.94438e+0,
      -2.35576e-1;
  if(node=="RLEG1")
    rC <<
      4.05183e-7,
      -3.83869e+0,
      2.19162e+1;
  if(node=="RLEG2")
    rC <<
      -3.28966e+0,
      5.01030e-1,
      3.47170e+0;
  if(node=="RLEG3")
    rC <<
      -7.18179e+1,
      7.58280e+0,
      -1.42801e+0;
  if(node=="RLEG4")
    rC <<
      -4.29165e+1,
      1.17240e+1,
      -2.82151e+0;
  if(node=="RLEG5")
    rC <<
      3.24289e+0,
      4.65209e+0,
      -7.32177e-1;
  if(node=="RLEG6")
    rC <<
      -2.48732e+1,
      7.85960e-2,
      3.82498e+0;
  if(node=="LLEG1")
    rC <<
      4.05183e-7,
      -3.83869e+0,
      2.19162e+1;
  if(node=="LLEG2")
    rC <<
      -3.28965e+0,
      -6.32384e-1,
      3.47170e+0;
  if(node=="LLEG3")
    rC <<
      -7.19284e+1,
      7.57808e+0,
      1.34158e+0;
  if(node=="LLEG4")
    rC <<
      -4.29459e+1,
      1.17224e+1,
      2.97258e+0;
  if(node=="LLEG5")
    rC <<
      3.24289e+0,
      4.65210e+0,
      7.81358e-1;
  if(node=="LLEG6")
    rC <<
      -2.48732e+1,
      7.85960e-2,
      3.82498e+0;
  if(node=="RARM1")
    rC <<
      5.69887e-2,
      3.59362e+1,
      1.10127e+1;
  if(node=="RARM2")
    rC <<
      -1.00180e-2,
      -9.91178e+0,
      -2.28432e+0;
  if(node=="RARM3")
    rC <<
      7.84674e-2,
      -2.96507e+0,
      -3.23713e+1;
  if(node=="RARM4")
    rC <<
      -5.29589e+0,
      4.62381e+1,
      5.06259e+0;
  if(node=="LARM1")
    rC <<
      -5.69861e-2,
      3.59362e+1,
      -1.10127e+1;
  if(node=="LARM2")
    rC <<
      -1.02610e-1,
      -9.91178e+0,
      -2.28305e+0;
  if(node=="LARM3")
    rC <<
      -2.62502e-2,
      2.94852e+0,
      -3.26378e+1;
  if(node=="LARM4")
    rC <<
      -5.29948e+0,
      4.62509e+1,
      -5.06689e+0;

  return rC;
}

Matrix3d R(string axis, double q)
{
  double s,c;
  Matrix3d R;

  s = sin(q);
  c = cos(q);

  if(axis=="z")
    R <<
      c,-s, 0,
      s, c, 0,
      0, 0, 1;
  if(axis=="y")
    R <<
      c, 0, s,
      0, 1, 0,
      -s,0, c;
  if(axis=="x")
    R <<
      1, 0, 0,
      0, c,-s,
      0, s, c;

  return R;
}

