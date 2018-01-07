/**
   @author Sho Miyahara 2017
*/

#include <string>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <math.h>

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

struct I{
  Matrix3d leg1;
  Matrix3d leg2;
  Matrix3d leg3;
  Matrix3d leg4;
  Matrix3d leg5;
  Matrix3d leg6;

  Matrix3d arm1;
  Matrix3d arm2;
  Matrix3d arm3;
  Matrix3d arm4;
} r,l;

Matrix3d R(string, double);

Matrix3d inertia(string);
Matrix3d RNode(string);
Matrix3d localInertia(string);

void output(Matrix3d);

int main()
{
  cout << "R leg Inertia tensor:" << endl;
  r.leg1 = inertia("RLEG1")*MM*MM;
  // cout << "R leg 1 Inertia tensor:" << endl;
  output(r.leg1);

  r.leg2 = inertia("RLEG2")*MM*MM;
  // cout << "R leg 2 Inertia tensor:" << endl;
  output(r.leg2);

  r.leg3 = inertia("RLEG3")*MM*MM;
  // cout << "R leg 3 Inertia tensor:" << endl;
  output(r.leg3);

  r.leg4 = inertia("RLEG4")*MM*MM;
  // cout << "R leg 4 Inertia tensor:" << endl;
  output(r.leg4);

  r.leg5 = inertia("RLEG5")*MM*MM;
  // cout << "R leg 5 Inertia tensor:" << endl;
  output(r.leg5);

  r.leg6 = inertia("RLEG6")*MM*MM;
  // cout << "R leg 6 Inertia tensor:" << endl;
  output(r.leg6);


  cout << "L leg Inertia tensor:" << endl;

  l.leg1 = inertia("LLEG1")*MM*MM;
  // cout << "L leg 1 Inertia tensor:" << endl;
  output(l.leg1);

  l.leg2 = inertia("LLEG2")*MM*MM;
  // cout << "L leg 2 Inertia tensor:" << endl;
  output(l.leg2);

  l.leg3 = inertia("LLEG3")*MM*MM;
  // cout << "L leg 3 Inertia tensor:" << endl;
  output(l.leg3);

  l.leg4 = inertia("LLEG4")*MM*MM;
  // cout << "L leg 4 Inertia tensor:" << endl;
  output(l.leg4);

  l.leg5 = inertia("LLEG5")*MM*MM;
  // cout << "L leg 5 Inertia tensor:" << endl;
  output(l.leg5);

  l.leg6 = inertia("LLEG6")*MM*MM;
  // cout << "L leg 6 Inertia tensor:" << endl;
  output(l.leg6);


  cout << "R arm Inertia tensor:" << endl;

  r.arm1 = inertia("RARM1")*MM*MM;
  // cout << "R arm 1 Inertia tensor:" << endl;
  output(r.arm1);

  r.arm2 = inertia("RARM2")*MM*MM;
  // cout << "R arm 2 Inertia tensor:" << endl;
  output(r.arm2);

  r.arm3 = inertia("RARM3")*MM*MM;
  // cout << "R arm 3 Inertia tensor:" << endl;
  output(r.arm3);

  r.arm4 = inertia("RARM4")*MM*MM;
  // cout << "R arm 4 Inertia tensor:" << endl;
  output(r.arm4);


  cout << "L arm Inertia tensor:" << endl;

  l.arm1 = inertia("LARM1")*MM*MM;
  // cout << "L arm 1 Inertia tensor:" << endl;
  output(l.arm1);

  l.arm2 = inertia("LARM2")*MM*MM;
  // cout << "L arm 2 Inertia tensor:" << endl;
  output(l.arm2);

  l.arm3 = inertia("LARM3")*MM*MM;
  // cout << "L arm 3 Inertia tensor:" << endl;
  output(l.arm3);

  l.arm4 = inertia("LARM4")*MM*MM;
  // cout << "L arm 4 Inertia tensor:" << endl;
  output(l.arm4);

  return 0;
}

Matrix3d inertia(string node)
{
  return RNode(node)*localInertia(node)*RNode(node).transpose();
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
    return R("z", M_PI/2);
  if(node=="RLEG2"||node=="LLEG2")
    return R("z", M_PI)*R("y", -M_PI/2);
  if(node=="RLEG3"||node=="LLEG3")
    return R("z", -M_PI/2)*R("y", -M_PI/2);
  if(node=="RLEG4"||node=="LLEG4")
    return R("z", -M_PI/2)*R("y", -M_PI/2);
  if(node=="RLEG5"||node=="LLEG5")
    return R("z", -M_PI/2)*R("y", -M_PI/2);
  if(node=="RLEG6"||node=="LLEG6")
    return R("z", M_PI)*R("y", -M_PI/2);

  if(node=="RARM1"||node=="LARM1")
    return R("x", -M_PI/2);
  if(node=="RARM2"||node=="LARM2")
    return R("z", M_PI/2);
  if(node=="RARM3"||node=="LARM3")
    return R("z", M_PI)*R("y", -M_PI/2);
  if(node=="RARM4"||node=="LARM4")
    return R("z", -M_PI/2)*R("y", -M_PI/2);

  return Matrix3d::Zero();
}

Matrix3d localInertia(string node)
{
  Matrix3d I;

  if(node=="BODY1")
    I <<
      4.77151e+3,-7.27252e+1, 5.49937e+2,
      -7.27252e+1, 5.33640e+3, 5.71186e+1,
      5.49937e+2, 5.71186e+1, 5.51773e+3;
  if(node=="BODY2")
    I <<
      7.26374e+2, 2.81664e+1, 1.02147e+1,
      2.81664e+1, 7.89590e+2,-5.05608e+0,
      1.02147e+1,-5.05608e+0, 2.74925e+2;
  if(node=="HEAD1")
    I <<
      9.51077e+0,-7.41228e-2,-1.05256e+0,
      -7.41228e-2, 6.40490e+0,-3.02325e-1,
      -1.05256e+0,-3.02325e-1, 4.97111e+0;
  if(node=="HEAD2")
    I <<
      3.20353e+1,-5.04880e+0,-6.55641e-2,
      -5.04880e+0, 3.51472e+1, 4.54066e-2,
      -6.55641e-2, 4.54066e-2, 2.59511e+1;

  if(node=="RLEG1")
    I <<
      2.77458e+1, 2.48926e-6, 1.08060e-6,
      2.48926e-6, 9.57690e+0,-1.29806e+0,
      1.08060e-6,-1.29806e+0, 2.37104e+1;
  if(node=="RLEG2")
    I <<
      6.31338e+1,-6.18885e-1, 1.01226e+0,
      -6.18885e-1, 5.55820e+1, 3.28855e-1,
      1.01226e+0, 3.28855e-1, 4.51904e+1;
  if(node=="RLEG3")
    I <<
      2.31713e+2, 1.44579e+1, 1.32330e+1,
      1.44579e+1, 4.72676e+2,-9.52495e+0,
      1.32330e+1,-9.52495e+0, 4.35755e+2;
  if(node=="RLEG4")
    I <<
      1.84076e+2,-3.29998e+0, 4.55079e+0,
      -3.29998e+0, 2.95317e+2,-8.29468e+0,
      4.55079e+0,-8.29468e+0, 2.25932e+2;

  if(node=="RLEG5")
    I <<
      5.94587e+1,-4.08202e-1,-7.20727e-2,
      -4.08202e-1, 4.59388e+1,-5.54424e-1,
      -7.20727e-2,-5.54424e-1, 5.11179e+1;
  if(node=="RLEG6")
    I <<
      1.55016e+2,-7.14057e-2, 1.70683e+1,
      -7.14057e-2, 1.39643e+2, 3.80602e-1,
      1.70683e+1, 3.80602e-1, 5.97968e+1;

  if(node=="LLEG1")
    I <<
      2.77458e+1, 2.48926e-6, 1.08060e-6,
      2.48926e-6, 9.57690e+0,-1.29805e+0,
      1.08060e-6,-1.29805e+0, 2.37104e+1;
  if(node=="LLEG2")
    I <<
      6.30681e+1, 2.93348e-1, 1.01227e+0,
      2.93348e-1, 5.55820e+1,-3.50678e-1,
      1.01227e+0,-3.50678e-1, 4.51248e+1;
  if(node=="LLEG3")
    I <<
      2.31801e+2, 1.49663e+1,-1.45158e+1,
      1.49663e+1, 4.73478e+2, 1.04350e+1,
      -1.45158e+1, 1.04350e+1, 4.36352e+2;
  if(node=="LLEG4")
    I <<
      1.82049e+2,-2.84645e+0,-4.79234e+0,
      -2.84645e+0, 2.91216e+2, 8.37920e+0,
      -4.79234e+0, 8.37920e+0, 2.22810e+2;
  if(node=="LLEG5")
    I <<
      5.94459e+1,-4.08202e-1, 4.99529e-1,
      -4.08202e-1, 4.59261e+1, 6.50510e-1,
      4.99529e-1, 6.50510e-1, 5.11179e+1;
  if(node=="LLEG6")
    I <<
      1.55016e+2,-7.14057e-2, 1.70683e+1,
      -7.14057e-2, 1.39643e+2, 3.80602e-1,
      1.70683e+1, 3.80602e-1, 5.97968e+1;

  if(node=="RARM1")
    I <<
      1.42087e+2,-5.75840e-2,-7.51591e-2,
      -5.75840e-2, 6.52462e+1, 3.39010e+1,
      -7.51591e-2, 3.39010e+1, 1.17938e+2;
  if(node=="RARM2")
    I <<
      1.53251e+2, 2.71682e-1, 2.07022e-1,
      2.71682e-1, 1.35628e+2,-1.53672e+1,
      2.07022e-1,-1.53672e+1, 7.07822e+1;
  if(node=="RARM3")
    I <<
      1.22386e+2, 9.41629e-2,-1.85832e-2,
      9.41629e-2, 1.09558e+2,-8.27732e-1,
      -1.85832e-2,-8.27732e-1, 5.65823e+1;
  if(node=="RARM4")
    I <<
      2.80658e+2,-2.40293e+0,-1.29926e+0,
      -2.40293e+0, 3.40780e+1, 1.85149e+1,
      -1.29926e+0, 1.85149e+1, 2.70963e+2;

  if(node=="LARM1")
    I <<
      1.42087e+2, 5.75829e-2,-7.51502e-2,
      5.75829e-2, 6.52462e+1,-3.39010e+1,
      -7.51502e-2,-3.39010e+1, 1.17938e+2;
  if(node=="LARM2")
    I <<
      1.53253e+2,-1.60475e-1, 2.49619e-1,
      -1.60475e-1, 1.35627e+2,-1.53617e+1,
      2.49619e-1,-1.53617e+1, 7.07801e+1;
  if(node=="LARM3")
    I <<
      1.20095e+2, 2.35113e-1,-2.30691e-1,
      2.35113e-1, 1.07647e+2, 8.96281e-1,
      -2.30691e-1, 8.96281e-1, 5.56209e+1;
  if(node=="LARM4")
    I <<
      2.81004e+2,-2.39305e+0, 1.29841e+0,
      -2.39305e+0, 3.40730e+1,-1.84659e+1,
      1.29841e+0,-1.84659e+1, 2.71298e+2;

  return I;
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

void output(Matrix3d I)
{
  cout << "   "  << "- ["
       << I(0,0) << ", " << I(0,1) << ", " << I(0,2) << "," << endl;
  cout << "   "  << "   " << I(1,0) << ", " << I(1,1) << ", " << I(1,2) << "," << endl;
  cout << "   "  << "   " << I(2,0) << ", " << I(2,1) << ", " << I(2,2) << "]"
       << endl;
}
