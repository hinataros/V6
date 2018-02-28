/**
   @author Sho Miyahara 2017
*/

#include <string>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <math.h>

#include <iomanip>
#include <limits>

#define MM 1e-3

#define BODY_JOINT1_MASS 1.59374e+0
#define BODY_JOINT2_MASS 4.97680e-1
#define HEAD_JOINT1_MASS 2.08892e-2
#define HEAD_JOINT2_MASS 6.69886e-2

#define BODY_LINK1 0.09e+3
#define BODY_LINK2 0.034e+3
#define HEAD_LINK1 0.081e+3
#define HEAD_LINK2 0.008e+3
#define WAIST_LINK1 0.055e+3
#define WAIST_LINK2 0.034e+3

using namespace std;
using namespace Eigen;

struct Mass{
  double baseCRB;
  double body1;
  double body2;
  double head1;
  double head2;
} m;

struct CoM{
  Vector3d baseCRB;
  Vector3d body1;
  Vector3d body2;
  Vector3d head1;
  Vector3d head2;
} com;

struct Inertia{
  Matrix3d baseCRB;
  Matrix3d body1;
  Matrix3d body2;
  Matrix3d head1;
  Matrix3d head2;
} I;

Matrix3d R(string, double);

void comBaseCRB(Mass&, CoM&);
Matrix3d RNode(string);
Vector3d transNode(string);
Vector3d posNode(string);
Vector3d localCoM(string);

void inertiaBaseCRB(Mass&, CoM&, Inertia&);
Matrix3d localInertia(string);
Matrix3d rotationInertia(Matrix3d, Matrix3d);
Matrix3d parallelInertia(Matrix3d, double, Vector3d);

int main()
{
  m.body1 = BODY_JOINT1_MASS;
  m.body2 = BODY_JOINT2_MASS;
  m.head1 = HEAD_JOINT1_MASS;
  m.head2 = HEAD_JOINT2_MASS;

  comBaseCRB(m, com);
  cout << setprecision(numeric_limits<double>::max_digits10);
  cout << "Mass of base consider CRB: " << endl << m.baseCRB << endl;;

  cout << "CoM positon of base consider CRB: " << endl << com.baseCRB*MM << endl;;

  inertiaBaseCRB(m, com, I);
  cout << "Inertia tensor of base consider CRB" << endl << I.baseCRB*MM*MM << endl;;

  return 0;
}

void comBaseCRB(Mass &m, CoM &com)
{
  double mtemp;
  Vector3d rCtemp;
  com.body2 = RNode("BODY2").transpose()*localCoM("BODY2");
  mtemp = m.body2;
  rCtemp = m.body2*(posNode("BODY2") + com.body2);

  // cout << "com.body2: " << endl <<
  //   setprecision(std::numeric_limits<double>::max_digits10) <<
  //   com.body2*MM<< endl;
  // cout << "rCtemp: " << endl <<
  //   setprecision(std::numeric_limits<double>::max_digits10) <<
  //   (posNode("BODY2") + com.body2)*MM << endl;

  com.body1 = RNode("BODY1").transpose()*localCoM("BODY1");
  mtemp += m.body1;
  rCtemp += m.body1*(posNode("BODY1") + com.body1);

  // cout << "com.body1: " << endl <<
  //   setprecision(std::numeric_limits<double>::max_digits10) <<
  //   com.body1*MM<< endl;// xに-0.034
  // cout << "rCtemp: " << endl <<
  //   setprecision(std::numeric_limits<double>::max_digits10) <<
  //   (rCtemp/mtemp)*MM << endl;

  com.head1 = RNode("HEAD1").transpose()*localCoM("HEAD1");
  mtemp += m.head1;
  rCtemp += m.head1*(posNode("HEAD1") + com.head1);

  // cout << "com.head1: " << endl <<
  //   setprecision(std::numeric_limits<double>::max_digits10) <<
  //   com.head1*MM<< endl;
  // cout << "rCtemp: " << endl <<
  //   setprecision(std::numeric_limits<double>::max_digits10) <<
  //   (rCtemp/mtemp)*MM << endl;

  com.head2 = RNode("HEAD2").transpose()*localCoM("HEAD2");
  mtemp += m.head2;
  rCtemp += m.head2*(posNode("HEAD2") + com.head2);

  // cout << "com.head2: " << endl <<
  //   setprecision(std::numeric_limits<double>::max_digits10) <<
  //   com.head2*MM<< endl;

  m.baseCRB = mtemp;

  com.baseCRB = rCtemp / m.baseCRB;

  // cout << com.baseCRB << endl;
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

  if(node=="LEG1")
    return R("z", -M_PI/2);
  if(node=="LEG2")
    return R("z", M_PI)*R("y", M_PI/2);
  if(node=="LEG3")
    return R("z", M_PI/2)*R("y", M_PI/2);
  if(node=="LEG4")
    return R("z", M_PI/2)*R("y", M_PI/2);
  if(node=="LEG5")
    return R("z", M_PI/2)*R("y", M_PI/2);
  if(node=="LEG6")
    return R("z", M_PI)*R("y", M_PI/2);

  if(node=="ARM1")
    return R("x", M_PI/2);
  if(node=="ARM2")
    return R("z", -M_PI/2);
  if(node=="ARM3")
    return R("z", M_PI)*R("y", M_PI/2);
  if(node=="ARM4")
    return R("z", M_PI/2)*R("y", M_PI/2);

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

void inertiaBaseCRB(Mass &m, CoM &com, Inertia &I)
{
  I.head1 = rotationInertia(localInertia("HEAD1"), RNode("HEAD1"));
  I.head2 = rotationInertia(localInertia("HEAD2"), RNode("HEAD2"));
  I.body1 = rotationInertia(localInertia("BODY1"), RNode("BODY1"));
  I.body2 = rotationInertia(localInertia("BODY2"), RNode("BODY2"));

  Matrix3d Itemp;
  double mtemp;

  Itemp = parallelInertia(I.head2, m.head2, com.head2);
  mtemp = m.head2;

  Itemp = parallelInertia(I.head1, m.head1, com.head1)+
    parallelInertia(Itemp, mtemp, transNode("HEAD2","HEAD1"));
  mtemp += m.head1;

  Itemp = parallelInertia(I.body1, m.body1, com.body1)+
    parallelInertia(Itemp, mtemp, transNode("HEAD1","BODY1"));
  mtemp += m.body1;

  Itemp = parallelInertia(I.body2, m.body2, com.body2)+
    parallelInertia(Itemp, mtemp, transNode("BODY1","BODY2"));
  mtemp += m.body2;

  I.baseCRB = parallelInertia(Itemp, mtemp, com.baseCRB-posNode("BODY2"));
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

  return I;
}

Matrix3d rotationInertia(Matrix3d I, Matrix3d R)
{
  return R*I*R.transpose();
}

Matrix3d parallelInertia(Matrix3d I, double m, Vector3d r)
{
  return I + m * (r.norm() * r.norm() * Matrix3d::Identity() - r*r.transpose());
}
